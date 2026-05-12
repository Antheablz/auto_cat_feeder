
function toggle_led_put(val) {
  console.log("toggle led", val);


  fetch('http://esp32s2.local/blink', {
    method: 'PUT',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({
      state: val
    }),
  })
  .then(response => response)
  // .then(response => response.json())
  .then(data => console.log('Success:', data))
  .catch(error => console.error('Error:', error));
}
