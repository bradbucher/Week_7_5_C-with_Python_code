#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
        To call this function, simply pass the function name in Python that you wish to call.
Example:
        callProcedure("printsomething");
Output:
        Python will print on the screen: Hello from python!
Return:
        None
*/
void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}

/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("PrintMe","Test");
Output:
        Python will print on the screen:
                You sent me: Test
Return:
        100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;


    return _PyLong_AsInt(presult);
}

/*
Description:
        To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
        int x = callIntFunc("doublevalue",5);
Return:
        25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(i)", param);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;

    return _PyLong_AsInt(presult);
}


int main()
{

    int user_choice = -1; //to select user choice
    while (user_choice != 4)      // continue until user enters 4- exit 
    {
        try  //handle exceptions, if user enters invalid data
        {

            cout << "======================================================== \nMENU\n"; //show menu to the user
            cout << "1. Check number of times each individual item appears\n";
            cout << "2. Determine the frequency of a specific item\n";
            cout << "3. Graphically display a data file as a text-based histogram\n";
            cout << "========================================================\n";
            cout << "Enter your choice : \n";

            cin >> user_choice; //read user choice

            if (user_choice == 1) //if user input is 1
            {
                cout << "Frequency of items is : \n";
                cout << callIntFunc("get_frequency_of_each_item", "frequency.dat") << "\n";  //call get frequency of each item function
            }
            else if (user_choice == 2) //if user enters 2
            {
                cout << "Enter an item name, for which you want the frequency : \n"; //call get frequency of single item 
                string item;
                cin >> item;
                cout << callIntFunc("get_frequency_of_single_item", item) << "\n";
            }
            else if (user_choice == 3)   // if user enters 3
            {
                cout << "The histogram format of the data is: \n";
                cout << callIntFunc("show_histogram", "") << "\n";  //call show histogram function
            }
            else
            {
                break;
            }
        }
        catch (...)
        {
            cout << "Error occured please check the entered values" << "\n";
        }
    }

}
