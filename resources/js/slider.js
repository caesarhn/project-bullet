
const slides = document.getElementsByClassName('slides')
const islides = document.getElementsByClassName('islides')
const next = document.getElementById('next')
const prev = document.getElementById('prev')

let i = 0

function moveSlide(){
    if(i < 2){
        i++
    }else{
        i = 0
    }

    for(let x=0; x < slides.length; x++){
        slides[x].classList.add('hidden')
        islides[x].classList.remove('bg-red-hcr')
    }
    slides[i].classList.remove('hidden')
    islides[i].classList.add('bg-red-hcr')
}

function moveSlidePrev(){
    if(i > 0){
        i--
    }else{
        i = 2
    }

    for(let x=0; x < slides.length; x++){
        slides[x].classList.add('hidden')
        islides[x].classList.remove('bg-red-hcr')
    }
    slides[i].classList.remove('hidden')
    islides[i].classList.add('bg-red-hcr')
}

next.addEventListener('click', () => {
    moveSlide()
})

prev.addEventListener('click', () => {
    moveSlidePrev()
})

let slideInterval = setInterval(function() {
    moveSlide()
  }, 4000);