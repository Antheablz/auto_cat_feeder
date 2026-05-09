// fetch('http://esp32s2.local/blink', {
//   method: 'PUT',
//   headers: { 'Content-Type': 'application/json' },
//   body: JSON.stringify({
//     state: 1
//   }),
// })
// .then(response => response)
// // .then(response => response.json())
// .then(data => console.log('Success:', data))
// .catch(error => console.error('Error:', error));

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







// Simple PUT request with a JSON body using fetch
// const element = document.querySelector('#put-request .date-updated');
// const element = document.getElementById('button-on');
// const requestOptions = {
//     method: 'PUT',
//     headers: { 'Content-Type': 'application/json' },
//     body: JSON.stringify({ title: 'Fetch PUT Request Example' })
// };
// fetch('http://esp32s2.local/blink', )
//     .then(response => response.json())
//     .then(data => element.innerHTML = data );