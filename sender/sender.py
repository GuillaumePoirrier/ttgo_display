import requests
import random
import time


for i in range(0,50):
    cpu=random.randrange(40, 110,1)
    gpu=random.randrange(40, 110,1)
    myobj = {"GPU": cpu,"CPU":gpu}
    url = 'http://192.168.1.26/post/'
    print(myobj)

    r = requests.post(url , json=myobj)
    time.sleep(3)
