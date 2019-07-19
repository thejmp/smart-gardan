"use strict";

const express = require("express");
const bodyParser = require("body-parser");
var request = require('request-json');
var client = request.createClient('https://io.adafruit.com/');
var data = [0, 0, 0, 0, 0, 0, 0];

const restService = express();

restService.use(
  bodyParser.urlencoded({
    extended: true
  })
);

setInterval(function() {
  client.get('api/v2/jpattull/feeds/soilplant1', function (err, res, body) {
    data[0] = body.last_value;
  });

  client.get('api/v2/jpattull/feeds/soilplant2', function (err, res, body) {
    data[1] = body.last_value;
  });

  client.get('api/v2/jpattull/feeds/soilplant3', function (err, res, body) {
    data[2] = body.last_value;
  });

  client.get('api/v2/jpattull/feeds/soilplant4', function (err, res, body) {
    data[3] = body.last_value;
  });

  client.get('api/v2/jpattull/feeds/soilplant5', function (err, res, body) {
    data[4] = body.last_value;
  });

  client.get('api/v2/jpattull/feeds/wateredplant', function (err, res, body) {
    data[5] = body.last_value;
  });

  client.get('api/v2/jpattull/feeds/waterlevel', function (err, res, body) {
    data[6] = body.last_value;
  });
  console.log(data);
}, 20000);

restService.use(bodyParser.json());

restService.get("/", function(req, res) {
  client.get('api/v2/promise333/feeds/soil', function(err, res, body) {
    data = body.last_value;
  });
  console.log(data);
});

restService.post("/soil", function(req, res) {
console.log(data);
if (req.body.queryResult.parameters.soil_musure) {
  if (req.body.queryResult.parameters.plantNames == "peppermint")
    var outputText = "Your Peppermint has " + data[0] + "% soil moisture";
  else if (req.body.queryResult.parameters.plantNames == "bush")
    var outputText = "Your Bush has " + data[1] + "% soil moisture";
  else if (req.body.queryResult.parameters.plantNames == "ivy")
    var outputText = "Your Ivy has " + data[2] + "% soil moisture";
  else if (req.body.queryResult.parameters.plantNames == "pepper")
    var outputText = "Your Pepper has " + data[3] + "% soil moisture";
  else if (req.body.queryResult.parameters.plantNames == "demo")
    var outputText = "Your demo has " + data[4] + "% soil moisture";
  else
    var outputText = "you don't have that type of plant";
} else {
  if (data[6])
    var outputText = "you have water left in the tank";
  else
    var outputText = "you need to refill the water";
}
  var temp = {
    google: {
      expectUserResponse: true,
      richResponse: {
        items: [
          {
            simpleResponse: {
              textToSpeech: outputText
            }
          }
        ]
      }
    }
  };
  var meassige = [
    {
      simpleResponses:
          {simpleResponses:[{
              textToSpeech: outputText,
              displayText: outputText
            }]
          }
    }
  ];
  return res.json({
    fulfillmentText: "soil site water",
    fulfillmentMessages: meassige,
    source: "soil site",
    payload: temp
  });
});

restService.post("/soilAlexa", function (req, res) {

  console.log(req.body.request);

  if (req.body.request.type == "LaunchRequest")
    var outputText = "welcome to the smart garden alexa skill";
  else
    var outputText = "other text";

  var resp = {
    outputSpeech: {
      type: "PlainText",
      text: outputText,
      playBehavior: "REPLACE_ENQUEUED"
    }

  };

  return res.json({
    response: resp
  });
});

restService.listen(process.env.PORT || 8000, function() {
  console.log("Server up and listening");
});
