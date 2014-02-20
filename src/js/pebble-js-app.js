
function jsonMaker() {
 var json = {};
 var response = {};
 var req = new XMLHttpRequest();
  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=2000', true);
  req.onload = function(e) {
    if (req.readyState == 4 && req.status == 200) {
      if(req.status == 200) {
        response = JSON.parse(req.responseText);
        //json[0] = response.data.length;
        //json[0] = 5;
		for(var i = 0, l = 6; i < l; i++) {
  			json[i] = response.data[i].display_name;
		}
		 // return json;

        //var short_name = result.list[0].main.temp;
        //var icon = result.list[0].main.icon;
        //Pebble.sendAppMessage({ "icon":icon, "temperature":temperature + "\u00B0C"});
      } else { console.log("Error"); }
    }
  }
  req.send(null);
  return json;
//return response;
}



Pebble.addEventListener("ready",
	function(e) {
		console.log("Javascript app ready");
	});

var response = {};

Pebble.addEventListener("appmessage",
	function(e) {


 var req = new XMLHttpRequest();
  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=30', true);
  req.onload = function(e) {
    if (req.readyState == 4 && req.status == 200) {
      if(req.status == 200) {
        var response = JSON.parse(req.responseText);
        //create and send json
        json = {};
        json[0] = 5;
        for(var i = 1; i < 6; i++) {
  			json[i] = response.data[i].display_name;
		}
        Pebble.sendAppMessage(json);
      } else { console.log("Error"); }
    }
  }
  req.send(null);




			/*
				if (e.payload["100"]){
		 var json = {};
		 var messages = {};
		 var req = new XMLHttpRequest();
		  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=50', true);
		  req.onload = function(e) {
		    // if (req.readyState == 4 && req.status == 200) {
		    //   if(req.status == 200) {
		       messages = JSON.parse(req.responseText);
        json[0] = messages.data.length;
        json[0] = 5;
        var l = 6
		for(var i = 1; i < l; i++) {
  			json[i] = messages.data[i].display_name;

		}		
				    		    console.log(json[0]);
		    		    		    console.log(json[1]);
		    		    		      			console.log(messages.data[0].display_name);
		  req.send(null);

				//}
		     // } else { console.log("Error"); }
		    }
		    		    console.log(json[0]);
		    		    		    console.log(json[1]);
		    		    		    //  			console.log(messages.data[0].display_name);



		    var returnData = Pebble.sendAppMessage(json);
		  }
		    console.log(json[0]);
		    console.log(json[1]);


  			console.log(json); /*
			for (var i = 0; i < 7; i++) {
				var person = {};
				person[0] = response.data[i].display_name;
				var returnData = Pebble.sendAppMessage(person);
			}*/
			//var returnData = Pebble.sendAppMessage(json);
		 
		/*if (e.payload["101"]) {
			var returnData = Pebble.sendAppMessage(json);
		}*/


	}
	
);

