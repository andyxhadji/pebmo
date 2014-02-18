Pebble.addEventListener("ready",
	function(e) {
		console.log("Javascript app ready");
	});

Pebble.addEventListener("appmessage",
	function(e) {
		console.log("Received message");
				if (e.payload["100"]){
		 var json = {};
		 var response = {};
		 var req = new XMLHttpRequest();
		  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=2000', true);
		  req.onload = function(e) {
		    if (req.readyState == 4 && req.status == 200) {
		      if(req.status == 200) {
		       response = JSON.parse(req.responseText);
		        //json[0] = response.data.length;
		       // json[0] = 6;
		       response[0] = response.data.length;
				for(var i = 0, l = 7; i < l; i++) {
					var person = {};
					person[0] = response.data[i].display_name;
					var returnData = Pebble.sendAppMessage(person);
				}
		        //var short_name = result.list[0].main.temp;
		        //var icon = result.list[0].main.icon;
		        //Pebble.sendAppMessage({ "icon":icon, "temperature":temperature + "\u00B0C"});
		      } else { console.log("Error"); }
		    }
		  }
		  req.send(null);
  			console.log(json); /*
			for (var i = 0; i < 7; i++) {
				var person = {};
				person[0] = response.data[i].display_name;
				var returnData = Pebble.sendAppMessage(person);
			}*/
			//var returnData = Pebble.sendAppMessage(json);
		} 
		if (e.payload["101"]) {
			var returnData = Pebble.sendAppMessage(json);
		}
	}
);

function jsonMaker() {
 var json = {};
 var response = {};
 var req = new XMLHttpRequest();
  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=2000', true);
  req.onload = function(e) {
    if (req.readyState == 4 && req.status == 200) {
      if(req.status == 200) {
        return JSON.parse(req.responseText);
        //json[0] = response.data.length;
       // json[0] = 6;
		for(var i = 0, l = 7; i < l; i++) {
  			json[i] = response.data[i].display_name;
		}
        //var short_name = result.list[0].main.temp;
        //var icon = result.list[0].main.icon;
        //Pebble.sendAppMessage({ "icon":icon, "temperature":temperature + "\u00B0C"});
      } else { console.log("Error"); }
    }
  }
  req.send(null);
//return response;

}
