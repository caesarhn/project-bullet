<!DOCTYPE html>
<html lang="en">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <meta name="description" content="sewa mobil mudah, sewa mobil mudah dan cepat, sewa mobil terpercaya, sewa avanza murah, CV HELLEN CHRISA HCR">
        <meta name="keywords" content="sewa mobil lampung, rental hiace, sewa fortuner, sewa mobil bandar lampung">
        <title>Sewa mobil murah - HCR Rental solusi sewa mudah</title>
        <link rel="shortcut icon" href="/logo-hcr.png">
        <script src="https://maps.googleapis.com/maps/api/js?v-beta&key=AIzaSyAdkwLsmw614EHlTLFKWZRRUVKRIPALKFc&libraries=places"></script>
        @vite([
            'resources/css/app.css', 
            'resources/js/header.js', 
            'resources/js/slider.js',
            'resources/js/gmap.js'
        ])
        <!-- Google tag (gtag.js) -->
        <script async src="https://www.googletagmanager.com/gtag/js?id=AW-16655648765">
        </script>
        <script>
            window.dataLayer = window.dataLayer || [];
            function gtag(){dataLayer.push(arguments);}
            gtag('js', new Date());

            gtag('config', 'AW-16655648765');
        </script>
    </head>
    <body>
        <a href="https://wa.me/6285368303446" class="z-1000">
            <div class="fixed flex right-3 bottom-2 w-40 h-14 bg-green-wa rounded-full overflow-hidden hover:w-44 z-1000">
                <img class="h-10 mt-2 ms-4" src="{{ asset('waicon.png') }}" alt="icon whatsapp"/>
                <div class="my-auto">
                    <h2 class="ms-2 text-white font-semibold">Whatsapp</h2>
                </div>
            </div>
        </a>
        <div id="main-header" class="fixed w-full sm:min-h-24 md:min-h-16 bg-slate-50 z-50 shadow-lg" dir="ltr">
            <div class="flex w-full">
                <div class="sm:w-0 md:w-5 lg:w-1/12"></div>
                <div class="my-auto">
                    <img class="sm:max-h-24 md:max-h-16" src="{{ asset('logo-hcr.webp') }}" alt="logo HCR Rental Mobil Lampung"/>
                </div>
                <div class="mx-3 my-auto">
                    <h1 class="font-bold text-left sm:text-lg md:text-lg text-blue-se">CV HELLEN CHRISA HCR</h1>
                    <p class="text-sm text-left text-red-hcr">Rental no.1 lampung</p>
                </div>
                <div class="sm:w-0 md:w-1/4 lg:w-1/3 xl:w-1/3 hidden"></div>
                <div class="grow min-h-20"></div>
                <div class="flex gap-10 sm:mx-5 md:mx-16 xl:mx-36 sm:my-8 md:my-5 sm:hidden md:flex text-blue-se">
                    <a class="text-2md font-semibold hover:text-red-hcr" href="#top">Home</a>
                    <a class="text-2md font-semibold hover:text-red-hcr" href="#product">Product</a>
                    <a class="text-2md font-semibold hover:text-red-hcr" href="#tentang-hcr">About</a>
                    <a class="text-2md font-semibold hover:text-red-hcr hidden" href="#layanan-lainya">About</a>
                </div>
                <div class="sm:blok md:hidden grow min-w-16">
                    <div class="absolute h-14 aspect-square text-blue-se right-0 my-4" id="toggle">
                        <img src="{{ asset('toggle.svg') }}" alt="icon toggle untuk menampilkan menu">
                    </div>
                    <div class="absolute flex-col bg-slate-100 hidden right-0 top-24 text-xl" id="menu">
                        <a class="text-2md font-semibold hover:text-red-hcr" href="#top">
                            <div class="w-44 hover:bg-blue-se">
                                <div class="my-4 text-center">Home</div>
                            </div>
                        </a>
                        <a class="text-2md font-semibold hover:text-red-hcr" href="#product">
                            <div class="w-44 hover:bg-blue-se">
                                <div class="my-4 text-center">Product</div>
                            </div>
                        </a>
                        <a class="text-2md font-semibold hover:text-red-hcr" href="#tentang-hcr">
                            <div class="w-44 hover:bg-blue-se">
                                <div class="my-4 text-center">About</div>
                            </div>
                        </a>
                    </div>
                </div>
            </div>
        </div>
        <div class="w-full sm:min-h-24 md:min-h-16"></div>
        <main class="min-h-screen w-full font-arial" id="top">
            <div>
                <div class="slides w-full sm:max-h-84 lg:max-h-120 overflow-hidden fade">
                    <img class="object-cover w-full sm:h-84 lg:h-120" src="{{ asset('hcr-banner-1.webp') }}" alt="hcr banner 1 sewa mudah dan bersahabat"/>
                </div>
                <div class="slides w-full sm:h-84 lg:h-120 overflow-hidden hidden fade">
                    <img class="object-cover w-full sm:h-84 lg:h-120" src="{{ asset('hcr-banner-2.webp') }}" loading="lazy" alt="hcr banner 2 tersedia antar jemput ke bandara"/>
                </div>
                <div class="slides w-full sm:h-84 lg:h-120 overflow-hidden hidden fade">
                    <img class="object-cover w-full sm:h-84 lg:h-120" src="{{ asset('hcr-banner-3.webp') }}" loading="lazy" alt="hcr banner 3 layanan 24 jam"/>
                </div>
                <div class="relative flex gap-3 w-fit bottom-10 mx-auto">
                    <div class="sm:w-2 md:w-3 lg:w-4 xl:w-5 aspect-square rounded-full border-2 border-blue-se islides"></div>
                    <div class="sm:w-2 md:w-3 lg:w-4 xl:w-5 aspect-square rounded-full border-2 border-blue-se islides"></div>
                    <div class="sm:w-2 md:w-3 lg:w-4 xl:w-5 aspect-square rounded-full border-2 border-blue-se islides"></div>
                </div>
                <div id="next" class="absolute sm:h-40 lg:h-80 sm:w-24 lg:w-52 sm:top-20 md:top-40 right-0 content-center">
                    <img src="{{ asset('hcr-icon-next.svg') }}" class="sm:w-10 md:w-20 m-auto opacity-70" alt="icon next banner">
                </div>
                <div id="prev" class="absolute sm:h-40 lg:h-80 sm:w-24 lg:w-52 sm:top-20 md:top-40 content-center">
                    <img src="{{ asset('hcr-icon-prev.svg') }}" class="sm:w-10 md:w-20 m-auto opacity-70" alt="icon prev banner">
                </div>
            </div>
            <br/>
            <div class="relative sm:w-11/12 lg:w-3/4 xl:w-1/2 mt-10 mx-auto">
                <section id="product">
                    <h1 class="sm:text-3xl md:text-4xl lg:text-4xl xl:text-3xl mb-8 text-center text-blue-se">Penawaran Terbaik <span class="text-red-hcr">Saat ini</span></h1>
                </section>
                <div class="grid sm:grid-cols-1 md:grid-cols-3 gap-5 text-blue-se">
                    <div class="w-full h-fit p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-3/5 overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('fortuner.webp') }}" alt="Sewa fortuner bandar lampung"/>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">Fortuner</h2>
                            <p class="sm:text-xs">Rp.1.500.000</p>
                            <p class="sm:text-xs">(tersedia lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar solar</li>
                                <li>7 Seater</li>
                                <li>4 Koper</li>
                            </ul>
                        </div>
                        <div class="relative m-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Fortuner%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                    <div class="w-full h-fit p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-3/5 overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('hiace-commuter.webp') }}" alt="sewa mobil hiace commuter"/>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">Hiace Commuter</h2>
                            <p class="sm:text-xs">Rp.1.500.000</p>
                            <p class="sm:text-xs">(tidak tersedia lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar solar</li>
                                <li>14 Seater</li>
                                <li>4 Koper</li>
                            </ul>
                        </div>
                        <div class="relative m-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Hiace%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                    <div class="w-full h-fit p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-3/5 overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('hiace-premio.webp') }}" alt="sewa mobil hiace premio"/>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">Hiace Premio</h2>
                            <p class="sm:text-xs">Rp.1.700.000</p>
                            <p class="sm:text-xs">(tidak tersedia lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar solar</li>
                                <li>14 Seater</li>
                                <li>4 Koper</li>
                            </ul>
                        </div>
                        <div class="relative m-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Hiace%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                </div>
                <div class="grid sm:grid-cols-1 md:grid-cols-3 gap-5 text-blue-se mt-5">
                    <div class="w-full h-fit p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-3/5 overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('innova.webp') }}" alt="sewa mobil innova ready lepas kunci" loading="lazy"/>
                            <div class="relative right-0 -top-5 h-5 w-28 text-center bg-red-600 text-white opacity-0">TERLARIS</div>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">Innova</h2>
                            <p class="sm:text-xs">Rp.500.000</p>
                            <p class="sm:text-xs">(lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar solar</li>
                                <li>7 Seater</li>
                                <li>4 Koper</li>
                                <li>Transmisi manual</li>
                            </ul>
                        </div>
                        <div class="relative m-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Innova%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                    <div class="w-full h-fit p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-3/5 overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('brio.webp') }}" alt="sewa mobil brio ready lepas kunci" loading="lazy"/>
                            <div class="relative right-0 -top-5 h-5 w-28 text-center bg-red-600 text-white">TERLARIS</div>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">All New Honda Brio</h2>
                            <p class="sm:text-xs">Rp.350.000</p>
                            <p class="sm:text-xs">(tersedia lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar Bensin</li>
                                <li>5 Seater</li>
                                <li>2 Koper</li>
                                <li>Transmisi manual</li>
                            </ul>
                        </div>
                        <div class="relative m-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Brio%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                    <div class="w-full h-fit p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-3/5 overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('avanza.webp') }}" alt="sewa mobil avanza ready lepas kunci" loading="lazy"/>
                            <div class="relative right-0 -top-5 h-5 w-28 text-center bg-red-600 text-white">TERLARIS</div>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">New Toyota Avanza</h2>
                            <p class="sm:text-xs">Rp.300.000</p>
                            <p class="sm:text-xs">(tersedia lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar Bensin</li>
                                <li>7 Seater</li>
                                <li>3 Koper</li>
                                <li>Transmisi manual</li>
                            </ul>
                        </div>
                        <div class="relative m-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Avanza%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                </div>
                <div class="grid sm:grid-cols-1 md:grid-cols-3 gap-5 text-blue-se mt-5">
                    <div class="relative w-full h-full p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-fit overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('all-new-avanza.webp') }}" alt="sewa mobil all new avanza ready lepas kunci" loading="lazy"/>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">All New Toyota Avanza</h2>
                            <p class="sm:text-xs">Rp.350.000</p>
                            <p class="sm:text-xs">(tersedia lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar Bensin</li>
                                <li>7 Seater</li>
                                <li>3 Koper</li>
                                <li>Transmisi manual</li>
                            </ul>
                        </div>
                        <div class="sm:relative md:absolute md:bottom-2 md:left-1/2 md:-translate-x-1/2 mx-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Avanza%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                    <div class="w-full h-fit p-2 border-2 border-blue-se rounded-xl">
                        <div class="w-full h-3/5 overflow-hidden rounded-t-xl">
                            <img class="object-cover" src="{{ asset('xpander.webp') }}" alt="sewa mobil all new xpander ready lepas kunci" loading="lazy"/>
                        </div>
                        <div class="mt-2">
                            <h2 class="sm:text-xl font-semibold mb-1 text-red-hcr">All New Mitsubishi Xpander</h2>
                            <p class="sm:text-xs">Rp.350.000</p>
                            <p class="sm:text-xs">(tersedia lepas kunci)</p>
                            <ul class="sm:text-xs list-inside list-disc mt-2">
                                <li>Bahan bakar Bensin</li>
                                <li>7 Seater</li>
                                <li>3 Koper</li>
                                <li>Transmisi manual</li>
                            </ul>
                        </div>
                        <div class="relative m-auto w-fit mt-2">
                            <a href="https://wa.me/6285368303446?text=Hallo%20HCR%2c%20Saya%20ingin%20sewa%20mobil%20Xpander%20apakah%20tersedia%20%3f">
                                <button type="button" class="bg-red-hcr rounded-xl px-5 py-1 text-white hover:bg-blue-se">Sewa Unit</button>
                            </a>
                        </div>
                    </div>
                </div>
            </div>
            <br/>
            <section id="layanan-lainya">
            <div class="relative sm:w-11/12 lg:w-3/4 xl:w-1/2 mt-10 mx-auto">
                <h1 class="sm:text-3xl md:text-4xl lg:text-4xl xl:text-3xl mb-8 text-center text-blue-se">Paket <span class="text-red-hcr">Layanan Lain</span></h1>
                <div class="flex gap-10 sm:flex-wrap md:flex-nowrap">
                    <div class="flex-auto bg-blue-se text-white p-5 rounded-md">
                        <h2 class="sm:text-xl md:text-lg mb-3 font-semibold">Jasa Pick Up/Drop Bandara</h2>
                        <p class="text-sm">All New Xenia/Avanza: 200K/drop</p>
                        <p class="text-sm">All New Terios: 200k/drop</p>
                        <p class="text-sm">All New Innova Reborn: 350k/drop</p>
                    </div>
                    <div class="flex-auto bg-blue-se text-white p-5 rounded-md">
                        <h2 class="sm:text-xl md:text-lg mb-3 font-semibold">Sewa Mobil + Driver</h2>
                        <p class="text-sm">All New Xenia/Avanza: 550K/hari</p>
                        <p class="text-sm">All New Terios: 550k/hari</p>
                        <p class="text-sm">All New Innova Reborn: 700k/hari</p>
                    </div>
                    <div class="flex-auto bg-blue-se text-white p-5 rounded-md">
                        <h2 class="sm:text-xl md:text-lg mb-3 font-semibold">Sewa Mobil + Driver + Bensin (All In)</h2>
                        <p class="text-sm">All New Xenia/Avanza: 700K/hari</p>
                        <p class="text-sm">All New Terios: 700k/hari</p>
                        <p class="text-sm">All New Innova Reborn: 900k/hari</p>
                        <p class="text-xs mt-2">*terdapat tambahan biaya bensin untuk luar kota</p>
                    </div>
                </div>
            </div>
            </section>
            <br/>
            <div class="relative sm:w-11/12 lg:w-3/4 xl:w-1/2 sm:mx-auto mt-10">
                <h1 class="sm:text-3xl md:text-4xl lg:text-4xl xl:text-3xl mb-8 text-center text-blue-se">Mengapa Sewa Mobil <span class="text-red-hcr">Melalui HCR</span></h1>
                <div class="flex flex-wrap px-auto gap-5/100 gap-y-10">
                    <div class="sm:w-full md:w-3/10">
                        <img src="{{ asset('hcr-icon-mudah-dan-praktis.svg') }}" class="sm:w-1/2 md:w-1/2 mx-auto" loading="lazy" alt="icon menggambarkan kemudahan"/>
                        <h2 class="sm:text-3xl md:text-xl text-center mt-5 mb-2 font-bold text-blue-se">Mudah & <span class="text-red-hcr">Fleksibel</span></h2>
                        <p class="sm:text-xl md:text-sm text-justify">Sistem reservasi kami yang user-friendly memungkinkan Anda untuk memesan kendaraan kapan saja dan di mana saja.</p>
                    </div>
                    <div class="sm:w-full md:w-3/10">
                        <img src="{{ asset('hcr-icon-harga-bersahabat.svg') }}" class="sm:w-1/2 md:w-1/2 mx-auto" loading="lazy" alt="icon menggambarkan harga yang bersahabat"/>
                        <h2 class="sm:text-3xl md:text-xl text-center mt-5 mb-2 font-bold text-blue-se">Harga <span class="text-red-hcr">Kompetitif</span></h2>
                        <p class="sm:text-xl md:text-sm text-justify">Kami menawarkan harga yang bersaing dengan berbagai paket penyewaan harian, mingguan, maupun bulanan yang fleksibel.</p>
                    </div>
                    <div class="sm:w-full md:w-3/10">
                        <img src="{{ asset('hcr-icon-berkualitas.svg') }}" class="sm:w-1/2 md:w-1/2 mx-auto" loading="lazy" alt="icon yang menggambarkan kualitas"/>
                        <h2 class="sm:text-3xl md:text-xl text-center mt-5 mb-2 font-bold text-blue-se">Berkualitas</h2>
                        <p class="sm:text-xl md:text-sm text-justify">Armada kami terdiri dari kendaraan terbaru dengan kondisi yang terawat dan bersih.</p>
                    </div>
                    <div class="sm:w-full md:w-3/10">
                        <img src="{{ asset('hcr-icon-pelayanan-24jam.svg') }}" class="sm:w-1/2 md:w-1/2 mx-auto" loading="lazy" alt="icon menggambarkan layanan 24 jam"/>
                        <h2 class="sm:text-3xl md:text-xl text-center mt-5 mb-2 font-bold text-blue-se">Dukungan <span class="text-red-hcr">24/7</span></h2>
                        <p class="sm:text-xl md:text-sm text-justify">Layanan pelanggan kami selalu siap membantu Anda 24 jam sehari, 7 hari seminggu.</p>
                    </div>
                    <div class="sm:w-full md:w-3/10">
                        <img src="{{ asset('hcr-icon-pelayanan-ramah.svg') }}" class="sm:w-1/2 md:w-1/2 mx-auto" loading="lazy" alt="icon menggambarkan pelayanan yang ramah"/>
                        <h2 class="sm:text-3xl md:text-xl text-center mt-5 mb-2 font-bold text-blue-se">Pelayanan <span class="text-red-hcr">Ramah</span></h2>
                        <p class="sm:text-xl md:text-sm text-justify">Staf kami siap melayani Anda dengan penuh keramahan dan profesionalisme untuk memastikan kepuasan Anda.</p>
                    </div>
                </div>
                <br/>
            </div>
            <br/>
            <div class="relative sm:w-11/12 lg:w-3/4 xl:w-1/2 mt-10 mx-auto" id="tentang-hcr">
                <h1 class="sm:text-3xl md:text-4xl lg:text-4xl xl:text-3xl mb-8 text-center text-blue-se">Tentang <span class="text-red-hcr">HCR</span></h1>
                <div class="p-3 bg-red-hcr rounded-lg border-4 border-blue-se">
                    <p class="sm:text-xl md:text-md xl:text-lg text-justify text-white font-sofadi font-bold">Di CV HELLEN CHRISA HCR, kami berdedikasi untuk menyediakan layanan rental mobil berkualitas tinggi dengan harga terjangkau untuk memenuhi berbagai kebutuhan transportasi Anda. Berdiri sejak 2007 dan setelah beberapa tahun akhirnya resmi menjadi perusahaan yang legal dengan nama CV HELLEN CHRISA HCR, kami terus berinovasi dan berkembang untuk memastikan setiap pelanggan mendapatkan pengalaman yang aman, nyaman, dan memuaskan.</p>
                </div>
                <div class="flex flex-wrap gap-1/10">
                <div class="sm:w-full md:w-4/11">
                    <br/>
                    <h2 class="sm:text-xl md:text-lg text-center text-blue-se">Visi</h2>
                    <p class="sm:text-xl md:text-sm text-justify">Visi kami adalah menjadi perusahaan rental mobil terdepan yang dikenal luas atas kualitas layanan prima, kendaraan berkualitas, serta komitmen terhadap kepuasan pelanggan.</p>
                </div>
                <div class="sm:w-full md:w-4/11">
                    <br/>
                    <h2 class="sm:text-xl md:text-lg text-center text-red-hcr">Misi</h2>
                    <p class="sm:text-xl md:text-sm text-justify">Misi kami adalah menawarkan solusi transportasi yang handal, fleksibel, dan efisien dengan beragam pilihan kendaraan yang dapat disesuaikan dengan kebutuhan Anda, baik untuk tujuan pribadi, bisnis, maupun wisata.</p>
                </div>
                </div>
                <br/>
                <p class="sm:text-xl md:text-sm">Di CV HELLEN CHRISA HCR, kami menawarkan berbagai jenis kendaraan yang dapat Anda pilih sesuai kebutuhan, termasuk:</p>
                <ul class="list-inside list-disc mt-2">
                    <li>Mobil Sedan</li>
                    <li>Mobil SUV</li>
                    <li>Mobil MPV</li>
                    <li>Mobil Mewah</li>
                    <li>Minibus</li>
                </ul>
                <p class="sm:text-xl md:text-sm mt-2 text-justify">Kami berkomitmen untuk selalu menyediakan layanan terbaik dan menjaga kepercayaan yang telah diberikan oleh pelanggan. Kepuasan Anda adalah prioritas utama kami, karena itulah kami selalu berupaya memberikan nilai lebih dalam setiap layanan yang kami tawarkan.</p>
            </div>
        </main>
        <div class="w-full sm:h-200 md:h-100 bg-red-hcr mt-20">
            <div class="relative sm:w-11/12 lg:w-7/8 xl:w-3/4 mx-auto mt-10">
                <div class="relative flex sm:gap-x-0 md:gap-x-32 gap-y-10 sm:flex-wrap md:flex-nowrap top-10">
                    <div class="sm:w-full md:w-auto">
                        <h2 class="text-lg text-white mb-3">Layanan Pelanggan</h2>
                        <div class="flex gap-5 mb-2">
                            <img src="{{ asset('hcr-icon-phone.svg') }}" class="h-12 my-auto" loading="lazy"/>
                            <div>
                                <h2 class="text-lg font-semibold text-white">085368303446 (Tomi)</h2>
                                <h2 class="text-lg font-semibold text-white">082280008848 (Mikel)</h2>
                            </div>
                        </div>
                        <div class="flex gap-5">
                            <img src="{{ asset('hcr-icon-email.svg') }}" class="h-12 my-auto" loading="lazy"/>
                            <div class="my-auto">
                                <h2 class="text-lg font-semibold text-white align-middle">support@sewamobillampunghcr.com</h2>
                            </div>
                        </div>
                    </div>
                    <div class="sm:w-full md:w-auto">
                        <h2 class="text-lg text-white mb-3">Temukan Kami</h2>
                        <div class="flex gap-5">
                            <a href="https://www.instagram.com/sewamobillampung.hcr">
                                <img src="{{ asset('ig.png') }}" class="w-12" alt="icon linked to instagram" loading="lazy"/>
                            </a>
                            <a href="https://wa.me/6285368303446">
                                <img src="{{ asset('waicon.png') }}" class="w-12" alt="icon linked to whatsapp" loading="lazy"/>
                            </a>
                        </div>
                    </div>
                    <div class="sm:w-full md:w-auto">
                        <h2 class="text-lg text-white mb-3">Lokasi</h2>
                        <p class="max-w-80 text-white text-sm mb-2">Jl Cipto Mangunkusumo Gg Punggut O, Sumur Batu, Teluk Betung utara, Bandar Lampung, Lampung, 35214</p>
                        <div id="map" class="sm:w-full md:w-80 sm:h-80 md:h-44 z-50"></div>
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>