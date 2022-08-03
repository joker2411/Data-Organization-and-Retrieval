# StockScrapper
This project is done for the assignment of Data Organization and Retrieval. I have retrieved the price value of 'Reliance' stocks over the period of 7 days from 22nd September 2021 to 29th September 2021 and calculated 30 distinct maximum and minimum prices overall and average price value for every day.

# Methodology
I have used mainly 3 steps as following throughout the course of the project in the same order as mentioned below :
1. Data Scrapping
2. Data Cleaning
3. Data Processing

# 1. Data Scrapping
I have used 'BeautifulSoup' to scrap the data from the NSE(National Stock Exchange) website. The required latest price value was inside a div tag with id name 'responseDiv'. I had to perform further processing steps to precisely get the required data from the HTML code fetched. Since the NSE is only open from Monday to Friday and 9:15 AM to 3:30 PM, so to get the data only between this intervel, we have used the datetime.now() function to fetch the current time and only run our script till 4 PM.
Since because of possibility of issues in connection, I needed to save the data in the system as well. For that I again used the datetime.now() function to fetch the current date. Based on the dates, I have created .CSV files accordingly to save stock price with their respective time. CSV file have 2 headers {"PRICE "," TIME "}. Data is kept for further cleaning and processing.

# 2. Data Cleaning
I have created another python module named 'processing' with function name 'find_results' for data cleaning. Due to bad connectivity, I have gotten few files in which instead of price value, a string 'None' got entered. To further use this data while processing, I dropped these entries in our CSV files which have 'None' as price value. I also removed duplicate entries in each CSV file so that we only use distinct values of the day to find results.

# 3. Data Processing
I am checking that if we have already fetched 7 or more CSV files then I am collecting their respective day number and passing that list as parameter in 'find_results' function in 'processing.py' module which then returns overall 30 maximum, 30 minimum and average price value of that day.
