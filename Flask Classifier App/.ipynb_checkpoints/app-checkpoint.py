from flask import Flask, render_template, url_for, request
from flask_bootstrap import Bootstrap
import numpy as np
import pandas as pd

# ML
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.externals import joblib

app = Flask(__name__)
Bootstrap(app)

# html
@app.route('/')
def index():
	return render_template('index.html')

# prediction
@app.route('/predict', methods=['POST'])
def predict():
    df = pd.read_csv("names_dataset.csv", index_col = 0)
    df_X = df.name
    df_Y = df.sex
    
    corpus = df_X
    cv = CountVectorizer()
    X = cv.fit_transform(corpus)
    
    namesdetector_model = open("naivebayesgendermodel.pkl", "rb")
    clf = joblib.load(namesdetector_model)
    
    if request.method == 'POST':
        namequery = request.form['namequery']
        data = [namequery]
        vect = cv.transform(data).toarray()
        my_prediction = clf.predict(vect)
    return render_template('results.html', prediction = my_prediction,name = namequery.upper())
    
    
	
if __name__ == '__main__':
	app.run(debug=True)