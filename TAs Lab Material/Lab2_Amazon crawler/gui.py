
import pandas as pd
import numpy as np
import re
from urllib.request import urlopen
from bs4 import BeautifulSoup
import urllib.request
import urllib.request
import requests
from bs4 import BeautifulSoup
import os 

#################################################################################################################################
from tkinter import *
from tkinter import messagebox
################################################################################################################################


tkWindow = Tk()  
tkWindow.configure(background='#CCCCFF')
tkWindow.geometry('450x250')  
tkWindow.title('Text, Image and Video Crawler')
cwd = os.getcwd()

########################################Function to scrap text data#########################################################################################

no_pages = 1
imagedownloadLinks=[]
def get_data(pageNo): 

	headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0", "Accept-Encoding":"gzip, deflate", "Accept":"text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", "DNT":"1","Connection":"close", "Upgrade-Insecure-Requests":"1"}
	#proxy = '103.15.60.23:8080'
	r = requests.get('https://www.amazon.in/s?bbn=1389401031&rh=n%3A976419031%2Cn%3A1389401031%2Cn%3A1389432031&dc&qid=1631382284&rnid=1389401031&ref=lp_1389401031_nr_n_1',headers=headers,timeout=1500)#proxies = {'http':proxy,'https':proxy},timeout=600)
	content = r.content
	soup = BeautifulSoup(content)
	#print(soup)
	alls = []
	counter=0;
    
	for d in soup.findAll('div', attrs={'class':'a-column a-span4'}):
		name = d.find('span', attrs={'class':'a-size-base-plus a-color-base a-text-normal'})
		price = d.find('span', attrs={'class':'a-price-whole'})
		olderprice=d.find('span', attrs={'class':'a-offscreen'})
		imageURL2 = d.find('img', attrs={'class':'s-image'})
		imageURL = imageURL2['src']
		all1=[]
		if name is not None:
			name1=name.text
			name1=name1.strip()
			all1.append(name1)
		else:
			all1.append("unknown-product")
            
		if price is not None:
			all1.append(price.text)
		else:
			all1.append("unknown-price")
        
		if olderprice is not None:
			olderprice1=olderprice.text
			olderprice1=olderprice1.strip()
			all1.append(olderprice1)
		else:
			all1.append("unknown-olderprice")
            
		if imageURL is not None:
			all1.append(imageURL)
		else:
			all1.append("unknown-URL")
            
		alls.append(all1)    
    
	return alls
#######################################Function to scrap images##########################################################################################

imagedownloadLinks=[]
def get_images(pageNo): 

	headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0", "Accept-Encoding":"gzip, deflate", "Accept":"text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", "DNT":"1","Connection":"close", "Upgrade-Insecure-Requests":"1"}
	r = requests.get('https://www.amazon.in/s?bbn=1389401031&rh=n%3A976419031%2Cn%3A1389401031%2Cn%3A1389432031&dc&qid=1631382284&rnid=1389401031&ref=lp_1389401031_nr_n_1',headers=headers,timeout=1500)#proxies = {'http':proxy,'https':proxy},timeout=600)
	content = r.content
	soup = BeautifulSoup(content)
	#print(soup)
	alls = []
	counter=0;
    
	for d in soup.findAll('div', attrs={'class':'a-column a-span4'}):
#Image scraping from webpage
#imageURL2=d.find('img')
		imageURL2=d.find('img',attrs={'class':'s-image'})
		imageURL=imageURL2['src']
		
		if imageURL is not None: 
			counter=counter+1
			urllib.request.urlretrieve(imageURL, cwd+"/Images/"+"Image "+"_"+str(counter)+".jpg")
            
############################Calling function to scrap images#####################################################################################################
def amazonImage():
	results = []
	no_pages = 1
	print("Getting images... ")
	get_images(no_pages)
#############################Calling function to scrap text data####################################################################################################

def amazonData():
	results = []
	print("Writing data to CSV file...")
	for i in range(1, no_pages+1):
		results.append(get_data(i))
	flatten = lambda l: [item for sublist in l for item in sublist] #flattens a list of lists to produce a single list
	df = pd.DataFrame(flatten(results),columns=['Mobile Name','Price','Old Price','URL'])	
	df.to_csv(cwd+'/amazon_products.csv', index=True, encoding='utf-8')

####################################Function to download video#############################################################################################


def get_video_data(): 

	headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:66.0) Gecko/20100101 Firefox/66.0", "Accept-Encoding":"gzip, deflate", "Accept":"text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8", "DNT":"1","Connection":"close", "Upgrade-Insecure-Requests":"1"}
	#proxy = '103.15.60.23:8080'
	r = requests.get('https://navbharattimes.indiatimes.com/video/news/kashmiri-boy-funny-reaction-on-injection-watch-viral-video/videoshow/86226291.cms',headers=headers,timeout=600)#proxies = {'http':proxy,'https':proxy},timeout=600)
	content = r.content
	soup = BeautifulSoup(content)
	#print(soup)
	alls = []
	counter=0;
    
	for d in soup.findAll("meta", itemprop="contenturl"):
		file_name = d["content"].split('/')[-1] 
        
		print( "Downloading file:%s"%file_name)
		r2 = requests.get(d["content"], stream = True)
		with open(file_name, 'wb') as f: 
			for chunk in r2.iter_content(chunk_size = 1024*1024): 
				if chunk: 
					f.write(chunk) 
          
		print( "%s downloaded!\n"%file_name )
		print ("All videos downloaded!")
		
    
########################################Buttons on UI################################################################################################
def endProgram():
    tkWindow.destroy()
    sys.exit()

b1 = Button(tkWindow,
	text = 'Amazon Mobile Models Data',
	activeforeground ='#0099ff',
	bd = '5',width=30,
	command = amazonData)
	
  

b2 = Button(tkWindow,
	text = 'Amazon Mobile Models Images',
	activeforeground ='#0099ff',
	bd = '5',width=25,
	command = amazonImage)  



b3 = Button(tkWindow,
	text = 'Vedio from News website',
	activeforeground ='#0099ff',
	bd = '5',width=25,
	command = get_video_data)  


b4 = Button(tkWindow,
	text = 'Exit',
	activeforeground ='#0099ff',
	bd = '5',width=30, command = endProgram)
    
b1.pack(side = TOP)  
  
b2.pack(side = LEFT)  
  
b3.pack(side = RIGHT)  
  
b4.pack(side = BOTTOM)  
tkWindow.mainloop()


#########################################################################################################################################

