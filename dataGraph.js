function loadScript(url) {
    var head = document.getElementsByTagName('head')[0];
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = url;
    head.appendChild(script);
}

// Chart.js is used to make a graphic display of data
loadScript("https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.9.4/Chart.js");

fetch('graph_data.csv')
    .then(response => response.text())
    .then(data => {
        // Process the CSV data here

    })
    .catch(error => {
        // Handle any errors that occur during the fetch operation
        console.log("dumb ass");
    });