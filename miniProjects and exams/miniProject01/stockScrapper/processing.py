import pandas as pd
import heapq

def find_results(day_list):
    maximum = list()
    minimum = list()
    day_average = list()

    for day_num in day_list:
        file_name = "day" + str(day_num) + ".csv"
        df = pd.read_csv(file_name)
        #         print("Dimension of "+file_name+" before None value deleteion is : {}\n".format(df.shape))

        df.dropna(inplace=True)

        for x in df.index:
            if (df.loc[x, "PRICE "] == "None"):
                df.drop(x, inplace=True)

        #         print("Dimension of "+file_name+" after None value deleteion is : {}\n".format(df.shape))

        df["PRICE "] = df["PRICE "].astype(float)

        prices = df["PRICE "]
        prices.drop_duplicates(inplace=True)

        day_average.append(round(sum(list(prices)) / len(list(prices)), 2))

        maximum = heapq.nlargest(30, list(prices) + maximum)
        minimum = heapq.nsmallest(30, list(prices) + minimum)

    return (maximum, minimum, day_average)