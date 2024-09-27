let lastScroll = 0

const header = document.getElementById('main-header')
const toggle = document.getElementById('toggle')
const menu = document.getElementById('menu')

window.addEventListener('scroll', () => {
    let scroll = document.documentElement.scrollTop
    //console.log(scroll)
    if(scroll > 100){
        if(scroll > lastScroll){
            header.classList.add('hide')
            menu.classList.add('hidden')
        }else{
            header.classList.remove('hide')
        }
    }
    lastScroll = scroll
})

toggle.addEventListener('click', () =>{
    menu.classList.toggle('hidden')
})