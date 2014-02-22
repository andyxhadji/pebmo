Pebble.addEventListener("showConfiguration",
	function(e) {
		Pebble.openURL();
		window.location.href = "pebblejs://close#" + encodeURIComponent(JSON.stringify(configuration));
	});
Pebble.addEventListener("webviewclosed",
	function(e){
		var configuration = JSON.parse(decodeURIComponent(e.response));
		console.log("Configuration window returned: ", JSON.stringify(configuration));
	})

Pebble.addEventListener("ready",
	function(e) {
		console.log("Javascript app ready");
	});

var response = {};
var json_final = {};
var id_array = [];
var id;
var amount;
Pebble.addEventListener("appmessage",
	function(e) {
		if (e.payload["100"]){
		 var req = new XMLHttpRequest();
		  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=200', true);
		  req.onload = function(e) {
		    if (req.readyState == 4 && req.status == 200) {
		      if(req.status == 200) {
		        var response = JSON.parse(req.responseText);
				var length = response.data.length;
				json_array = [];
				for(var j = 0; j < length; j++) {
					json_array.push(response.data[j].display_name);
					id_array.push(response.data[j].id);
				}
				json_array.sort();
		        json_final[0] = length;
		        for(var k = 1; k < length+1; k++) {
		  			json_final[k] = json_array[k-1];
				}

		        Pebble.sendAppMessage(json_final);
		      } else { console.log("Error"); }
		    }
		  }
		  req.send(null);
		} else if(e.payload["200"]) {
			var index = e.payload["200"];
			var name = json_final[index+1];
			id = id_array[index];
			amount = e.payload["300"];
			console.log(name);
			console.log(id);
		}
		

	}
	
);

