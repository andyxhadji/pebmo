Pebble.addEventListener("showConfiguration",
	function(e) {
		Pebble.openURL("https://api.venmo.com/v1/oauth/authorize?client_id=1615&scope=make_payments,access_friends&response_type=code");
		//window.location.href = "pebblejs://close#" + encodeURIComponent(JSON.stringify(configuration));
	});
Pebble.addEventListener("webviewclosed",
	function(e){
		console.log(e.response);
		var array = e.response.split(",");
		window.localStorage.setItem(0, array[0]);
		window.localStorage.setItem(1, array[1]);
		//var configuration = JSON.parse(decodeURIComponent(e.response));
		//console.log("Configuration window returned: ", JSON.stringify(configuration));
	});

Pebble.addEventListener("ready",
	function(e) {
		console.log("Javascript app ready");
	});

var response = {};
var json_final = {};
var id_array = [];
var old_json = [];
var id;
var amount;

Pebble.addEventListener("appmessage",
	function(e) {
		if (e.payload["100"]){
		 var req = new XMLHttpRequest();
		  req.open('GET', 'https://api.venmo.com/v1/users/' + window.localStorage.getItem(1) + '/friends?access_token=' + window.localStorage.getItem(0) + '&limit=200', true);
		  req.onload = function(e) {
		    if (req.readyState == 4 && req.status == 200) {
		      if(req.status == 200) {
		        var response = JSON.parse(req.responseText);
				var length = response.data.length;
				json_array = [];
				for(var j = 0; j < length; j++) {
					json_array.push(response.data[j].display_name);
					old_json.push(response.data[j].display_name);
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
			console.log(window.localStorage.getItem(0));
			var index = e.payload["200"];
			var name = json_final[index+1];
			var id_index;
			for(var y = 0; y < old_json.length; y++){
				if (name == old_json[y]){
					id_index = y;
					break;
				}
			}
			id = id_array[id_index];
			amount = e.payload["300"];
			console.log(name);
			console.log(id);
			var url = "https://api.venmo.com/v1/payments";
			var params = "access_token=" + window.localStorage.getItem(0) + "&user_id=" + id + "&note=-Pebmo&amount=" + amount;
			console.log(params);
			var http = new XMLHttpRequest();
			http.open("POST", url, true);
			//Send the proper header information along with the request
			http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
			http.setRequestHeader("Content-length", params.length);
			http.setRequestHeader("Connection", "close");

			http.onreadystatechange = function() {//Call a function when the state changes.
			    if(http.readyState == 4 && http.status == 200) {
			        alert(http.responseText);
			    }
			}
			http.send(params);
		}
		

	}
	
);

