import re
import string


def frequency_of_each_item(filename):
	frequencies = {}

	with open(filename, 'r') as f:
		for word in f.read().splitlines():
			frequencies[word] = frequencies.get(word, 0) + 1

	with open('frequency.dat', 'w') as f:
		for word, freq in frequencies.items():
			print(word, freq, file=f)

	return 0                
        
      
        
        
def get_frequency_of_single_item(item_name):#this method returns a string which contains the given item & respective frequency
    filename = "frequency.dat"  #give your input file name here, it should be in the same directory where python code is present
    f= open(filename, "r")  #open input data file
    if not f:
        print("Could not open the file, please check the file name") #print error message if , file is not opened
    else:
        data= f.read()  #read file read
        list_of_items= data.split()   #split the data into individual items & store them in a list
        frequency = {}  # dictionary to store item:frequeny
        for item in list_of_items:
            frequency[item]= frequency.get(item,0)+1   #calculating frequency
            
        if item_name in frequency:  #if given item is present in the string
            return frequency[item_name]  #return the frequency
        return "NO such item present"  #else return no such item present
        
def show_histogram(string=""):
    filename = "frequency.dat"  #give your input file name here, it should be in the same directory where python code is present
    f= open(filename, "r")  #open input data file
    if not f:
        print("Could not open the file, please check the file name") #print error message if , file is not opened
    else:
        data= f.read()  #read file read
        list_of_items= data.split()   #split the data into individual items & store them in a list
        frequency = {}  # dictionary to store item:frequeny
        for item in list_of_items:
            frequency[item]= frequency.get(item,0)+1   #calculating frequency
        
        ans=""  #answer string
        for item,freq in frequency.items():
            ans+=item + " " +  '*'* freq + '\n'  #appending item, '*' no.of times the item occures
            
        return ans #returning answer
