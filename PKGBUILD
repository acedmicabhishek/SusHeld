pkgname=susheld
pkgver=1.0.0
pkgrel=1
pkgdesc="An SDL-based screensaver"
arch=('x86_64')
url="https://github.com/acedmicabhishek/SusHeld"
license=('GPL')
depends=('sdl2' 'sdl2_image' 'gcc' 'make' 'cmake')  # Dependencies
makedepends=('cmake')
source=("git+https://github.com/acedmicabhishek/SusHeld.git")
sha256sums=('SKIP')

build() {
    
    cd "$srcdir/SusHeld"
    rm -rf build
    mkdir -p build
    cd build
    cmake ..
    make
}

package() {
    # Navigate to the build directory where the executable is located
    cd "$srcdir/SusHeld/build"
    
    # Ensure the 'SusHeld' executable is being correctly installed to the appropriate directory
    install -Dm755 SusHeld "$pkgdir/usr/bin/susheld"
    
    # Install the logo if it exists
    if [ -f "$srcdir/SusHeld/logo.png" ]; then
        install -Dm644 "$srcdir/SusHeld/logo.png" "$pkgdir/usr/share/susheld/logo.png"
    fi
}
