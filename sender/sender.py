import requests
import random
import time
import json


while 1!=0:
    
    ohm='http://192.168.1.43:8085/data.json'
    r = requests.get(ohm)
    gpu=json.loads(r.text)['Children'][0]['Children'][1]['Children'][2]['Children'][5]['Value']
    cpu=json.loads(r.text)['Children'][0]['Children'][0]['Children'][1]['Children'][0]['Value']

    gpu = gpu.split(',')[0]
    cpu = cpu.split(',')[0]
    myobj = {"GPU": gpu,"CPU":cpu}
    url = 'http://192.168.1.26/post/'
    print(myobj)
    r = requests.post(url , json=myobj)
    time.sleep(5)
