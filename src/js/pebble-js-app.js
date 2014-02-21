Pebble.addEventListener("ready",
	function(e) {
		console.log("Javascript app ready");
	});

var response = {};

Pebble.addEventListener("appmessage",
	function(e) {

		if (e.payload["100"]){
		 var req = new XMLHttpRequest();
		  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=50', true);
		  req.onload = function(e) {
		    if (req.readyState == 4 && req.status == 200) {
		      if(req.status == 200) {
		        var response = JSON.parse(req.responseText);
		        //create and send json
		        json = {};
		        json[0] = 40;
		        for(var i = 1; i < 41; i++) {
		  			json[i] = response.data[i].display_name;
				}
		        Pebble.sendAppMessage(json);
		      } else { console.log("Error"); }
		    }
		  }
		  req.send(null);
		}

	}
	
);

