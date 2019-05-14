import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    username = session["username"]
    user_id = session["user_id"]

    # Query database for users cash amount
    rows = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)

    # Get current cash amount
    cash = round(rows[0]["cash"], 2)

    # Query database for users stocks and number of shares
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as shares, ROUND(SUM(price)) as price FROM transactions WHERE id = :id GROUP BY symbol HAVING SUM(shares) > 0", id=user_id)

    return render_template("index.html", username=username, stocks=stocks, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    username = session["username"]
    user_id = session["user_id"]

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # look up the stocks current price
        stock = lookup(request.form.get("symbol"))

        # ensure input symbol is not blank
        if not request.form.get("symbol"):
            return apology("Must enter stock symbol")

        # ensure ticker symbol is valid
        if stock == None:
            return apology("Invalid stock symbol")

        # ensure share amount is entered
        if not request.form.get("shares"):
            return apology("Must enter amount of shares to buy")

        # ensure share amount if integer and positive
        x = request.form.get("shares")
        if x < 1 or x.isdigit() == False:
            return apology("Shares must be a positive number", 400)

        # Query database for users cash amount
        rows = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=user_id)

        # Get current cash amount
        cash = rows[0]["cash"]

        # Get price of stock
        price = stock["price"]

        # Get number of shares requested
        shares = int(request.form.get("shares"))

        # Price of stock x number of shares
        total_price = price * shares

        # If total price higher than available cash return insufficient funds
        if total_price > cash:
            return apology("Insufficient funds")

        # If sufficient funds, update cash by subtracting the total amount
        db.execute("UPDATE users SET cash = cash - :total_price WHERE id = :id", id=user_id, total_price=total_price)

        # Add the user's transaction to the transactions table
        db.execute("INSERT INTO transactions(id, symbol, shares, type, price) VALUES (:id, :symbol, :shares, :type, :total_price)",
                id=user_id, symbol=stock["symbol"], shares=shares, type="BUY", total_price=total_price)

        # flash success and reload app
        flash("Stock purchased successfully.")
        return redirect("/")

    else:
        return render_template("buy.html", username=username)


@app.route("/check", methods=["GET"])
def check():
    """Return true if username available, else false, in JSON format"""

    username = request.args.get('username', 1)

    # Query database for username
    rows = db.execute("SELECT * FROM users WHERE username = :username", username=username)
    if len(rows) == 1:
        return jsonify(False)
    else:
        return jsonify(True)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = session["user_id"]
    username = session["username"]

    # query database for history
    history = db.execute(
        "SELECT symbol, shares, type, price, date_time FROM transactions WHERE id = :id ORDER BY date_time DESC", id=user_id)

    return render_template("history.html", username=username, history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Remember username
        session["username"] = request.form.get("username")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    username = session["username"]

    if request.method == "POST":

        stock = lookup(request.form.get("symbol"))

        # ensure ticker symbol is valid
        if stock == None:
            return apology("Invalid stock symbol")

        price = stock["price"]
        name = stock["name"]

        return render_template("quoted.html", price=usd(price), name=name)

    else:
        return render_template("quote.html", username=username)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure password confirmation matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        # Ensure user does not already exist
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        if len(rows) == 1:
            return apology("user already exists")

        hash = generate_password_hash(request.form.get("password"))

        # If the gauntlet ran successfully, insert the user into the database
        insert = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
        username=request.form.get("username"), hash=hash)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Remember the username to display in nav bar
        session["username"] = rows[0]["username"]

        flash("Your account has been created. Welcome to CS50 Finance!")
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session["user_id"]
    username = session["username"]

    # query database for users stocks where share holdings sum is positive
    rows = db.execute(
        "SELECT symbol, SUM(shares) as shares FROM transactions WHERE id = :id GROUP BY symbol HAVING SUM(shares) > 0", id=user_id)

    if request.method == "POST":

        # amount of shares and symbol
        amount = int(request.form.get("shares"))
        symbol = request.form.get("symbol")

        # error if not stocks are selected
        if not request.form.get("symbol"):
            return apology("Must select a stock symbol")

        # error if user selects too many stocks (does not own that many)
        shares = db.execute("SELECT SUM(shares) as shares FROM transactions WHERE id = :id AND symbol = :symbol AND shares > 0",
                            id=user_id, symbol=symbol)

        if int(request.form.get("shares")) > int(shares[0]["shares"]):
            return apology("You do not own that many shares")

        # if successful, query database for users cash amount
        rows = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        cash = rows[0]["cash"]

        # look up the stocks current price
        stock = lookup(request.form.get("symbol"))
        price = stock["price"]

        # calculate total price
        total_price = price * amount

        # Update cash by adding to the users cash balance
        db.execute("UPDATE users SET cash = cash + :total_price WHERE id = :id", id=user_id, total_price=total_price)

        # Add the user's transaction to the transactions table (negative shares and price as SELL)
        db.execute("INSERT INTO transactions(id, symbol, shares, type, price) VALUES (:id, :symbol, :shares, :type, :total_price)",
                id=user_id, symbol=symbol, shares=-abs(amount), type="SELL", total_price=-abs(total_price))

        flash("Stock sold successfully.")
        return redirect("/")

    else:
        return render_template("sell.html", username=username, rows=rows)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
