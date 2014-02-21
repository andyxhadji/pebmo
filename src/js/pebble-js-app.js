Pebble.addEventListener("ready",
	function(e) {
		console.log("Javascript app ready");
	});

var response = {};

Pebble.addEventListener("appmessage",
	function(e) {

 var req = new XMLHttpRequest();
  req.open('GET', 'https://api.venmo.com/v1/users/1235690780098560886/friends?access_token=sZTpf6f7Q6KUa53CyxpCaHKrse9RAHzE&limit=50', true);
  req.onload = function(e) {
    if (req.readyState == 4 && req.status == 200) {
      if(req.status == 200) {
        var response = JSON.parse(req.responseText);
        //create and send json
        /*json = {};
        json[0] = 40;
        for(var i = 1; i < json[0]+1; i++) {
  			json[i] = response.data[i].display_name;
		}*/
		var length = 40;
		json_array = [];
		for(var j = 0; j < length; j++) {
			json_array.push(response.data[j].display_name);
		}
		json_array.sort();
		json_final = {};
        json_final[0] = length;
        for(var k = 1; k < length+1; k++) {
  			json_final[k] = json_array[k-1];
		}

        Pebble.sendAppMessage(json_final);
      } else { console.log("Error"); }
    }
  }
  req.send(null);

	}
	
);

