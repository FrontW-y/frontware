import qrcode

class QRC:
    def __init__(self, adress):
        self.qr = qrcode.QRCode(
            version=1,
            error_correction=qrcode.constants.ERROR_CORRECT_L,
            box_size=5,
            border=1,
        )
        self.qr.add_data(adress)
        self.qr.make(fit=True)
        self.img = self.qr.make_image(fill_color="black", back_color="white")
        self.img.save("qrcode.png")
    
    def getQr(self):
        return "qrcode.png"