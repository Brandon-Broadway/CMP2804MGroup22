## Wheelie Smart Application
The Wheelie Smart application is a proof of concept application to show how an autonomous robotic wheelie bin can be controlled from a mobile application. Currently, it does not allow for any control over a robotic device, but a video showing this working has been included within the download file.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

## Prerequisites
What things you need to install the software and how to install them
A computer running an up-to-date version of Android Studio, capable of running a virtual machine.
OR an Android phone running Android Nougat 7.1 or later.

## Installing
A step by step series of examples that tell you how to get a development env running
Download the WheelieSmart application file from this GitHub repository, then using Android Studio go to File -> Open -> then go to the file’s location and select ‘App’.

## Usage
When using this application, you are able to create multiple templates for wheelie bins that include a name, code, and date, summarising the days each individual bin will go out on a weekly basis (Monday, Tuesday, etc.). The user is also able to remove a bin from the list of created bins by entering the bin's code. This code should be unique thanks to some error handling included within the code.

## Testing
1.	From the first window (the home screen) press the button labelled ‘manage bins’. Then press the button labelled ‘Back to Home’. This should work exactly as explained, but this ensures that the app can function without a bin list being filled already.
2.	Back on the home screen, press the button labelled ‘Add New Bin’. From this field, follow each page and go through the process of creating a new bin, naming and changing the details as you like. From there, go to the ‘manage bins’ page. This tests to ensure that you can actually create a test bin using the settings provided.
3.	Add a new bin using the same name or code as one you have previously made. This tests the fact that you cannot create repeat bins, as within a real-world environment this would invalidate the idea of secure bins.

## Built With
•	Kotlin – The base framework and the language this was coded in.
•	Android Studio – The IDE used.
•	Java - Used for additional functionality.
•	Gson – Used for additional functionality.

## Versioning
This is the most recent and up-to date version of the project and can be considered the first working release. Any later developments will be released on this branch of Github.

## Authors
•	George Monk – Back-end development of Kotlin files.
•	Kean Noon – Front-end development of .Xml files.
See also the list of Contributors who participated in this project.

## Contributors
•	Alex Scoley – Extensive user testing.
•	Brandon Broadway – User testing.
•	Nathan Carrington – User testing.
•	Amar Panesar – Server development.
•	Fionn O’Connor – Robot development.

## Bugs
No known bugs are present within this application, if any are found please email wheeliesmart@gmail.co.uk detailing the error you found and how you came across it.

