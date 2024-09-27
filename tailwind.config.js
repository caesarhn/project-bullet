/** @type {import('tailwindcss').Config} */
export default {
  content: [
    './resources/**/*.blade.php',
    './resources/**/*.js',
  ],
  theme: {
    screens: {
      'sm': '300px',
      'md': '800px',
      'lg': '1300px',
      'xl': '1600px'
    },
    extend: {
      fontFamily: {
        arial: ['Arial', 'sans-serif'],
        sofadi: ['"Sofadi One"', 'cursive'],
      },
      inset: {
        '3/100': '3.333%',
        '1/8': '12.5%',
        '3/10': '41%',
        '3/20': '32%',
        '7/8': '87.5%'
      },
      gap: {
        '3/100': '3.333%',
        '1/10': '10%',
        '5/100': '5%',
      },
      width: {
        '3/10': '30%',
        '4/11': '45%',
        '100': '25rem'
      },
      height: {
        '100': '25rem',
        '104': '26rem',
        '108': '27rem',
        '112': '28rem',
        '116': '29rem',
        '120': '30rem',
        '150': '37.5rem',
        '200': '50rem',
        '240': '60rem'
      },
      colors: {
        'red-hcr': 'rgb(138,15,0)',
        'blue-hcr': 'rgb(31,70,147)',
        'blue-se': 'rgb(41,106,148)',
        'blue-minor': 'rgb(217, 227, 244)',
      },
      zIndex: {
        '1000': '1000',
      }
    },
  },
  plugins: [],
}

