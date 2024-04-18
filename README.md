# Military Academy
![image](https://github.com/JusDooEt/MilitaryAcademy/assets/152052216/3ef9c89b-e414-46f6-9931-262303a02c9b)

![image](https://github.com/JusDooEt/MilitaryAcademy/assets/152052216/d268e400-e16e-42fb-97af-e47ef4cd6934)

## Newest Changes
- Added a clear button and the button's functionality to the roster list, applicant log list, and the application data fields. This will clear the UI component listing the applicants and the txt file that is storing the data when the program is closed.
- Added a roster.txt file that will save the roster state when the program is closed and will be reloaded the next time the program is relaunched.


## About
This program will allow the user to enter data for a person applying to a military academy. The program will use defined minimum and maximum values for age, weight, and height per gender to compare against the applicants data that was input into the program. A different gender will have different requirement values in order to be admitted to the academy. The program will display the applicants name, age and sex to the roster text edit, on the right hand side of the program, if the applicant is accepted to the academy.

## Class
### Applicants
This class has variable members for an applicant's name, sex, age, weight, height, and acceptance status. It also has the appropriate mutators and accessors to correlate with the class variable members. This class also has a public validate function that uses the sex, age, weight and height variable members to set the applicant's acceptance status to true or false. The validate function can be called from anywhere in the program since it is defined as a public function. This class also includes a print function that will print the details of an individual applicant to the console for debugging purposes. 

### AppLogDialog
This class defines a dialog box that can be dynamically created in the main application code. This class will read from the applicantList.txt file in order to create a vector of applicants and fill out the item list component in the UI. When a user double clicks an applicant in the item list component, the selected applicant's full details will be displayed in the lower text edit. Reading from the applicantList.txt file will allow the program to read a history of applicant data even if the data was entered in previous sessions. This allows the "state" of the application to be saved and for a history of data to be stored after the user closes the application.

## To-Do
- [x] Create a new tab to display all of the people who have applied and all of their personal data.
- [x] Create an output file for the roster and all applicants to “save” progress when closing and relaunching the program.
- [x] Create a clear button in the appLogDialog to clear the list and the text file.


