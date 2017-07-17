var TOKEN = 'YOUR_ACCESS_TOKEN';

var konekuta = require('konekuta');
var express = require('express');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);
var hbs = require('hbs');
var printIps = require('./get_ips');

// Some options for express (node.js web app library)
hbs.registerPartials(__dirname + '/views/partials');
app.use(express.static(__dirname + '/public'));
app.set('view engine', 'html');
app.set('views', __dirname + '/views');
app.engine('html', hbs.__express);

if (!process.env.TOKEN && TOKEN === 'YOUR_ACCESS_TOKEN') {
    throw 'Please set your access token first in main.js!';
}

// This is how we go from device => view model
// we'll use this to render the device view, this will also be sent to the client
// when a device connects (so it knows what to render)
function mapToView(d) {
    var hex = Number(d.color).toString(16);
    var model = {
        name: d.name || d.endpoint,
        endpoint: d.endpoint,
        moisture: (Number(d.moisture) * 100).toFixed(2)
    };

    // create the device HTML
    var html = hbs.handlebars.compile('{{> device}}')(model);

    return { model: model, html: html };
}

var options = {
    endpointType: 'test',     // what endpoint types to look for
    token: TOKEN,
    io: io,
    deviceModel: {                    // building the initial device model (w/ 4 properties)
        moisture: {
            retrieve: '/moisture/0/value',    // when device registers, retrieve value
            subscribe: true
        },
    },
    timeout: 20000,
    mapToView: mapToView,
    verbose: true,  // Verbose logging
};

// Start konekuta (connects to mbed Cloud, and retrieves initial device model)
konekuta(options, (err, devices, ee, connector) => {
    if (err) {
        console.error('Error connecting to mbed Cloud...', err);
        return;
    }

    // Now we can start the web server
    server.listen(process.env.PORT || 5265, process.env.HOST || '0.0.0.0', function () {
        printIps();

        console.log('Web server listening on port %s!', process.env.PORT || 5265);
    });

    // And handle requests
    app.get('/', function (req, res, next) {
        // Render index view, with the devices based on mapToView function
        res.render('index', { devices: devices.map(d => mapToView(d).model) });
    });
});
