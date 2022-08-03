'''
    NAME - AMBUJ MISHRA
    STUDENT ID - 2021PCS1017
'''


import requests
from bs4 import BeautifulSoup
import time
from datetime import datetime
import os
import processing

def fetch_NSE_stock_price(stock_code):
    stock_url = 'https://www1.nseindia.com/live_market/dynaContent/live_watch/get_quote/GetQuote.jsp?symbol=' + str(stock_code)
    headers = {'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/79.0.3945.117 Safari/537.36'}
    response = requests.get(stock_url, headers = headers)
    soup = BeautifulSoup(response.text, 'html.parser')
    data_array = soup.find(id='responseDiv')
    data_array = data_array.getText().strip().split(":")

    for item in data_array:
        if 'lastPrice' in item:
            index = data_array.index(item) + 1
            latest_price = data_array[index].split('"')[1]
            latest_price = latest_price.replace(',','')
            return float(latest_price)

now = datetime.now()
today = int(now.strftime("%d"))
current_time = int(now.strftime("%H"))
base_date = 21
today = today-base_date

# print(today)
# print(current_time)

all_files = os.listdir('.')
count = 0
day_numbers = list()

for files in all_files:
    if(files[0:3] == 'day'):
        count = count+1
        day_numbers.append(int(files[3]))

day_numbers.sort()

if(count >= 7):
    m1, m2, d = processing.find_results(day_numbers)
    print("30 MAXIMUM VALUES OVER THE PERIOD OF 7 DAYS :\n{},\n\n30 MINIMUM VALUES OVER THE PERIOD OF 7 DAYS :\n{},\n\nAVERAGE DISTINCT PRICE VALUE OF 7 DAYS :\n{}".format(m1, m2, d))

else:
    filename = "day"+str(today)+".csv"
    #print(filename)
    f = open(filename, 'w')
    headers = "PRICE , TIME \n"
    f.write(headers)
    delay_time = 5

    while(current_time != 16):
        now = datetime.now()
        current_time = int(now.strftime("%H"))
        recorded_time = now.strftime("%H:%M:%S")
        price_value = fetch_NSE_stock_price("RELIANCE")
        print("{}, {}".format(price_value, recorded_time))
        print(str(price_value)+','+str(recorded_time),file = f)
        time.sleep(delay_time)

    f.close()