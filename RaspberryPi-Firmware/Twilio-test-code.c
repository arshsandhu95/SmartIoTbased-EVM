#include <string.h> //Library for manipulating arrays of characters
#include <iostream.h> //For input/output

#include "twilio.hh" //Twilio library


int main(int argc, char** argv) //Start of main
{
	string sid = "AC81e2d59bdf60bd4aefbaf2b30d76cd37";//Accout SID
	string autht = "344e89c5ba87dc7726d26ac31aa48136"; //Authentication token
	string from = "+12058466632"; //Twilio account no
	string to = "+14379806370"; //User number 
	string body = "Dear Arsh, Your vote casted successfully. Thank you!"; //Message body


	client = Client(sid, autht); //Storing details in client function




	string message = resp.message(); //Storing resp message in string function message
	unsigned int code = resp.code(); //Storing message response code in integer code
	twilio_httpstatus = resp.http_status(); //Storing http status 

	printf ("%s \n", "Http Response:",twilio_httpstatus);//Printing Http API response
	printf ("%s \n", "Message Response:",message); //Printing messgae response from Twilio
	printf ("%d \n", "Response code:",code);//Message sent response code

	return 0; 
}
