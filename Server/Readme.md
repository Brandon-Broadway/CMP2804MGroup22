# Implementing Azure

Implementing Azure resources and services for Application and Device communication

## Getting Started

These instructions will show you how to implement Azure services for communication through HTML POST and GET requests

### Prerequisites

Required

```
Microsoft Azure Subscription
Azure Functions
Cosmos Db
Logic Apps
```

### Setup

### Cosmos db

Firstly Create a database to store the incoming data from the Application:

Navigate to All Services and search for "cosmos db"
Select Azure Cosmos db

<img width="1211" alt="Screenshot 2020-04-16 at 11 22 06" src="https://user-images.githubusercontent.com/62295554/79558689-76867c00-809c-11ea-8333-2d79a391fe6d.png">

Click on Add to create a database

<img width="1211" alt="Screenshot 2020-04-16 at 11 22 19" src="https://user-images.githubusercontent.com/62295554/79558750-987ffe80-809c-11ea-9d0d-08e9e61fb2f9.png">

Create the database following image below


```
Only Change the:

* Subscription
* Resource Group
* Account Name

```

<img width="1211" alt="Screenshot 2020-04-16 at 11 21 42" src="https://user-images.githubusercontent.com/62295554/79558891-c9603380-809c-11ea-8ae3-d0facd165a82.png">


### Azure Functions

Next implement Azure Functions to receive POST data from the Application

Again navigate to all services and search for "functions"
Select Function

<img width="1211" alt="Screenshot 2020-04-17 at 12 01 08" src="https://user-images.githubusercontent.com/62295554/79562641-4db5b500-80a3-11ea-8f5b-35b7f2dfb963.png">

Click on Add to create the Function app

<img width="1211" alt="Screenshot 2020-04-17 at 12 01 16" src="https://user-images.githubusercontent.com/62295554/79562660-51493c00-80a3-11ea-8e7d-e65f69ff9255.png">

Create the function app using by following the image below

```
Only Change the:

* Subscription
* Resource Group
* Function Name

```

<img width="1211" alt="Screenshot 2020-04-17 at 12 02 00" src="https://user-images.githubusercontent.com/62295554/79562686-55755980-80a3-11ea-86e7-04e9c5b4d6db.png">


### Azure Logic App


Implement Azure Logic Apps for GET request. Push data from database to device

Go back to All services and search for "logic apps"
Select Logic Apps

<img width="1211" alt="Screenshot 2020-04-17 at 11 38 01" src="https://user-images.githubusercontent.com/62295554/79560881-4fca4480-80a0-11ea-91b7-eb56cd9912e1.png">


Click on Add to create a logic application

<img width="1211" alt="Screenshot 2020-04-17 at 11 38 14" src="https://user-images.githubusercontent.com/62295554/79560893-55278f00-80a0-11ea-8f62-045622b40b05.png">

Create the logic app using by following the image below

```
Only Change the:

* Subscription
* Resource Group
* Account Name

```

<img width="1211" alt="Screenshot 2020-04-17 at 11 38 44" src="https://user-images.githubusercontent.com/62295554/79560907-5a84d980-80a0-11ea-88e9-54d9d7e94101.png">

Logic app is ready for code

### Setup Function to recieve data and store in the Cosmos Database (Post request)

In the Function app page
Click on New Function

<img width="1211" alt="Screenshot 2020-04-17 at 12 22 02" src="https://user-images.githubusercontent.com/62295554/79564586-de41c480-80a6-11ea-9a4b-57e405e0c793.png">

Choose the HTTP trigger template

<img width="1211" alt="Screenshot 2020-04-17 at 12 29 22" src="https://user-images.githubusercontent.com/62295554/79564768-2c56c800-80a7-11ea-8748-e7de9ae50561.png">

Replace the Hello Name Template code with the code below

<img width="1211" alt="Screenshot 2020-04-17 at 12 36 14" src="https://user-images.githubusercontent.com/62295554/79565225-32997400-80a8-11ea-99f6-129a7e7627ad.png">


Enter this code:

```
#r "Newtonsoft.Json"
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using Microsoft.Extensions.Logging;

public static IActionResult Run(HttpRequest req, out object taskDocument, ILogger log)
{
    string binCode = req.Query["binCode"];
    string binName = req.Query["binName"];
    string day = req.Query["day"];

    string requestBody = await new StreamReader(req.Body).ReadToEndAsync();
    dynamic data = JsonConvert.DeserializeObject(requestBody);

    // We need both name and task parameters.
    if (!string.IsNullOrEmpty(binCode) && !string.IsNullOrEmpty(binName))
    {
        taskDocument = new
        {
            binCode,
            binName,
            day,
            goingOutSettings
        };

        return (ActionResult)new OkResult();
        
    }
    else
    {
        taskDocument = null;
        return (ActionResult)new BadRequestResult();

    }

}

```
Navigate to the Intergate tab and click on new output
We need to add the Cosmos database as the output of the data receieved. 

<img width="1211" alt="Screenshot 2020-04-17 at 12 39 01" src="https://user-images.githubusercontent.com/62295554/79565406-9459de00-80a8-11ea-98be-5b71f504a637.png">

Add your Cosmos Database to function. (where you want the data to be stored)

<img width="1211" alt="Screenshot 2020-04-17 at 12 42 50" src="https://user-images.githubusercontent.com/62295554/79565609-f87ca200-80a8-11ea-8250-8df883472101.png">

Save and run the code

Use the Function URL provided to Post data

<img width="599" alt="Screenshot 2020-04-17 at 12 46 20" src="https://user-images.githubusercontent.com/62295554/79565916-8a84aa80-80a9-11ea-9d79-82c6aa367dd0.png">


### Setup Logic apps to push the database data to the device (GET request)

Navigate to Logic app designer and click on "When HTTP request is received"
You will end up with this

<img width="727" alt="Screenshot 2020-04-17 at 12 52 38" src="https://user-images.githubusercontent.com/62295554/79566450-7beac300-80aa-11ea-9691-d47e95588d1c.png">

Request Body JSON Schema:

```
{
    "properties": {
        "binCode": {
            "type": "string"
        },
        "binName": {
            "type": "string"
        },
        "day": {
            "type": "string"
        },
        "id": {
            "type": "string"
        }
    },
    "type": "object"
}
```
Next add an Cosmos db action which will get the data from the database

<img width="818" alt="Screenshot 2020-04-17 at 12 55 13" src="https://user-images.githubusercontent.com/62295554/79566612-c1a78b80-80aa-11ea-81d1-2bc5d659f0b4.png">

Add a Response action (this is what the user will see in the GET request)

<img width="784" alt="Screenshot 2020-04-17 at 12 57 33" src="https://user-images.githubusercontent.com/62295554/79566819-14814300-80ab-11ea-8ef7-a22f7eb5305f.png">

Save and Run the Logic App

Remember the HTML GET request URL

<img width="694" alt="Screenshot 2020-04-17 at 13 00 50" src="https://user-images.githubusercontent.com/62295554/79567109-878ab980-80ab-11ea-86c4-a0e3413410cf.png">


## Running the tests

Use Postman Application to test if the Cloud Server can push out recieved data


<img width="1130" alt="Screenshot 2020-04-17 at 11 34 50" src="https://user-images.githubusercontent.com/62295554/79567164-a25d2e00-80ab-11ea-97da-e450df9f6572.png">


## Authors

* **Amar Panesar**
