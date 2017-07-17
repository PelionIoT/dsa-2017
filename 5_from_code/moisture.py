import mbed_connector_api
import time
import base64
import os

TOKEN = "YOUR_ACCESS_KEY"

connector = mbed_connector_api.connector(TOKEN)

def notificationHandler(data):
    for n in data['notifications']:
        print "Got a notification for %s: %s -> new value %s" % (n['ep'], n['path'], base64.b64decode(n['payload']))

connector.startLongPolling()
connector.setHandler('notifications', notificationHandler)

e = connector.getEndpoints("dsa-sensor")
while not e.isDone():
    None
if e.error:
    raise(e.error.error)
print("Found %d moisture sensors: %s" % (len(e.result), str(e.result)))

for endpoint in e.result:
    # Get a notification whenever the PIR count changes
    connector.putResourceSubscription(endpoint['name'], "/moisture/0/value")

while 1:
    time.sleep(1.0)
