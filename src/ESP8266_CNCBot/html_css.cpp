#include <ESP8266WiFi.h>
#include <Arduino.h>


String WiFiList_page (int net_num) {
	String 	webpage =  F("<!DOCTYPE html><html><head>\n<title>Move bot</title>\n");
			webpage += F("<style type=\"text/css\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n");
			
			webpage += F("body h3 {color: #444444;margin-bottom: 10px;font-size:80px}\n");

			webpage += F(".myButton {background-color:#f1f1f1;border:1px solid #bdbdbd;");
			webpage += F("display:block;width:100%;color:#383838;font-family:Times New Roman;");
			webpage += F("font-size:60px;padding:30px 10px;text-decoration:none;");
			webpage += F("text-shadow:1px 1px 2px #ffffff;}\n");
			webpage += F(".myButton:hover{background-color:#e9e9e9;}\n");

			webpage += F(".myButton2 {background-color:#f1f1f1;border:1px solid #bdbdbd;");
			webpage += F("display:block;width:50%;color:#383838;font-family:Times New Roman;");
			webpage += F("font-size:60px;padding:5px 10px;text-decoration:none;");
			webpage += F("text-shadow:1px 1px 2px #ffffff;text-align:center;}\n");
			webpage += F(".myButton2:hover{background-color:#e9e9e9;}\n");

			webpage += F("</style>\n</head>\n<body>\n");

			webpage += F("<h3>Select net</h3>\n");

    		for (int i = 0; i < net_num; i++) {
				webpage += F("<a class=\"myButton\" href=\"/savedParam?ssid=");
				webpage += WiFi.SSID(i);
				webpage += F("\">");
				webpage += WiFi.SSID(i);
				webpage += F("</a>\n");
			}

			webpage += F("</body>\n</html>\n");
	return webpage;
}

String NetParam_page(String got_ssid, String got_pass, bool saved) {
	String 	webpage = F("<!DOCTYPE html>\n");
		webpage += F("<html>\n");
		webpage += F("<head>\n");
		
		webpage += F("<title>Net param</title>\n");
		
		webpage += F("<style type=\"text/css\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n");
		
		webpage += F("body h3 {color:#444444;margin-bottom: 10px;font-size:80px;font-family:Times New Roman;}\n");

		webpage += F("input[type=password] {width: 75%;padding: 30px 20px;margin: 8px 0;");
		webpage += F("box-sizing: border-box;font-size:60px;font-family:Times New Roman;}\n");

		webpage += F("input[type=text] {width: 75%;padding: 30px 20px;margin: 8px 0;");
		webpage += F("box-sizing: border-box;font-size:60px;font-family:Times New Roman;}\n");

		webpage += F("input[type=submit] {width: 25%;padding: 30px 20px;margin: 8px 0;");
		webpage += F("box-sizing: border-box;font-size:60px;font-family:Times New Roman;}\n");

		webpage += F("input[type=checkbox] {width:80px;height:80px}\n");

		webpage += F("label {color:#444444;font-size:60px;font-family:Times New Roman;}");
		webpage += F("</style>\n");
		
		webpage += F("<head>\n");
		webpage += F("<body>\n");
		webpage += F("<h3>Net parameters");
		if (saved) webpage += F(" saved");
		webpage += F("</h3>");
		
		webpage += F("<form action=\"/saveParam\">");
		webpage += F("<label for=\"ssid\">SSID:</label><br>");
		webpage += F("<input type=\"text\" id=\"ssid\" name=\"ssid\" value=\"");
		webpage += got_ssid;
		webpage += F("\"><br>");
		webpage += F("<label for=\"pass\">Password:</label><br>");
		webpage += F("<input type=\"password\" id=\"pass\" name=\"pass\" value=\"");
		webpage += got_pass;
		webpage += F("\"><br>");
		webpage += F("<label>Show password   </label><input type=\"checkbox\"onclick=\"myFunction()\"><br><br>");
		webpage += F("<input type=\"submit\" href=\"&save=1\" value=\"Save\">");
		webpage += F("</form>");
		webpage += F("<script>\nfunction myFunction() {\n");
		webpage += F("var x = document.getElementById(\"pass\");\n");
		webpage += F("if (x.type === \"password\") {x.type = \"text\";}");
		webpage += F("else {x.type = \"password\";}\n}\n</script>");
		webpage += F("<body>\n");
		webpage += F("</html>");

	return webpage;
}

String BotParam_page(String got_ssid, String got_pass, bool saved) {
	String 	webpage = F("<!DOCTYPE html>\n");
		webpage += F("<html>\n");
		webpage += F("<head>\n");
		
		webpage += F("<title>Bot param</title>\n");
		
		webpage += F("<style type=\"text/css\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n");
		
		webpage += F("body h3 {color:#444444;margin-bottom: 10px;font-size:80px;font-family:Times New Roman;}\n");

		webpage += F("input[type=password] {width: 75%;padding: 30px 20px;margin: 8px 0;");
		webpage += F("box-sizing: border-box;font-size:60px;font-family:Times New Roman;}\n");

		webpage += F("input[type=text] {width: 75%;padding: 30px 20px;margin: 8px 0;");
		webpage += F("box-sizing: border-box;font-size:60px;font-family:Times New Roman;}\n");

		webpage += F("input[type=submit] {width: 25%;padding: 30px 20px;margin: 8px 0;");
		webpage += F("box-sizing: border-box;font-size:60px;font-family:Times New Roman;}\n");

		webpage += F("input[type=checkbox] {width:80px;height:80px}\n");

		webpage += F("label {color:#444444;font-size:60px;font-family:Times New Roman;}");
		webpage += F("</style>\n");
		
		webpage += F("<head>\n");
		webpage += F("<body>\n");
		webpage += F("<h3>Bot parameters");
		if (saved) webpage += F(" saved");
		webpage += F("</h3>");
		
		webpage += F("<form action=\"/newBotParam\">");
		webpage += F("<label for=\"ssid\">MY ID:</label><br>");
		webpage += F("<input type=\"text\" id=\"ssid\" name=\"ssid\" value=\"");
		webpage += got_ssid;
		webpage += F("\"><br>");
		webpage += F("<label for=\"pass\">Token:</label><br>");
		webpage += F("<input type=\"password\" id=\"pass\" name=\"pass\" value=\"");
		webpage += got_pass;
		webpage += F("\"><br>");
		webpage += F("<label>Show token   </label><input type=\"checkbox\"onclick=\"myFunction()\"><br><br>");
		webpage += F("<input type=\"submit\" href=\"&save=1\" value=\"Save\">");
		webpage += F("</form>");
		webpage += F("<script>\nfunction myFunction() {\n");
		webpage += F("var x = document.getElementById(\"pass\");\n");
		webpage += F("if (x.type === \"password\") {x.type = \"text\";}");
		webpage += F("else {x.type = \"password\";}\n}\n</script>");
		webpage += F("<body>\n");
		webpage += F("</html>");

	return webpage;
}
