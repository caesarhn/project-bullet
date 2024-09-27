async function initMap() {
    var myLatLng = {lat: -5.379103, lng: 105.252184}; // Ganti koordinat dengan lokasi yang diinginkan

    var map = new google.maps.Map(document.getElementById('map'), {
        center: myLatLng,
        zoom: 15
    });
    const marker = new google.maps.Marker({
    position: myLatLng,   

    map: map,
    icon: {
        path: google.maps.SymbolPath.CIRCLE,
        //url:'/marker.webp',
        scale: 8,
        fillColor: 'red',
        fillOpacity: 1,
        strokeColor: 'red',
        strokeWeight: 2,
        titel: 'HCR Rental Mobil'
    }
    });
}
initMap()