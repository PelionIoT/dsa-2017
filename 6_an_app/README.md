# Connected Lights Web Application

This is the web application that goes with the article [Building an internet connected lighting system](), in which we build a lighting system on top of the ARM mbed IoT Device Platform.

To get started, install a recent version of [node.js](https://nodejs.org/en/). Then:

```bash
$ npm install
$ TOKEN=xxx node main.js    # xxx = mbed Cloud Access Token
```

Now go to http://localhost:5265 to see your connected lights.

## Architecture

This application is built on top of [Konekuta](https://github.com/armmbed/konekuta), a node.js library to quickly build dynamic web applications on top of mbed Cloud.

The server side source code is relatively compact. In [main.js](main.js) we declare which devices we want to find (`deviceType`) and which resources on these devices to retrieve, which resources to subscribe to, and which resources can be updated. We also tell Konekuta how to map the data from mbed Cloud into a view (used to render the web application). Konekuta will now set up a socket connection to every connected client, sync changes from one client to another, store data in mbed Cloud, and will notify clients when a device changes it status (either update the `/pir/0/count`, disappears or comes back online).

On the client we'll connect to the server, and subscribe to events from the server. We then update the UI based on these updates. This ensures that every connected client will always see the same UI. Changing the color of a light on your desktop will also update the color on your phone.

To update data we can send events to the server over the same socket. The server will send the data back to Connector and tell the sender whether the action succeeded. If the action succeeded the server will also inform all other clients.

Konekuta also has logic for handling disconnects, going from offline to online, and other features to synchronize data.
