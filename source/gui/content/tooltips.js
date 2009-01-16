function check_answer(pinconv) {

        //pinconv = pinconv.replace(/5/g, "");

		pinconv = pinconv.replace(/v1/g, "ǖ");
		pinconv = pinconv.replace(/v2/g, "ǘ");
		pinconv = pinconv.replace(/v3/g, "ǚ");
		pinconv = pinconv.replace(/v4/g, "ǜ");
		pinconv = pinconv.replace(/v5/g, "ü");
		pinconv = pinconv.replace(/ve1/g, "ǖe");
		pinconv = pinconv.replace(/ve2/g, "ǘe");
		pinconv = pinconv.replace(/ve3/g, "ǚe");
		pinconv = pinconv.replace(/ve4/g, "ǜe");
		pinconv = pinconv.replace(/ve5/g, "üe");
		pinconv = pinconv.replace(/vn1/g, "ǖn");
		pinconv = pinconv.replace(/vn2/g, "ǘn");
		pinconv = pinconv.replace(/vn3/g, "ǚn");
		pinconv = pinconv.replace(/vn4/g, "ǜn");
		pinconv = pinconv.replace(/vn5/g, "ün");

		pinconv = pinconv.replace(/a1/g, "ā");
		pinconv = pinconv.replace(/a2/g, "á");
		pinconv = pinconv.replace(/a3/g, "ǎ");
		pinconv = pinconv.replace(/a4/g, "à");
		pinconv = pinconv.replace(/a5/g, "a");
		pinconv = pinconv.replace(/ai1/g, "āi");
		pinconv = pinconv.replace(/ai2/g, "ái");
		pinconv = pinconv.replace(/ai3/g, "ǎi");
		pinconv = pinconv.replace(/ai4/g, "ài");
		pinconv = pinconv.replace(/ai5/g, "ai");
		pinconv = pinconv.replace(/an1/g, "ān");
		pinconv = pinconv.replace(/an2/g, "án");
		pinconv = pinconv.replace(/an3/g, "ǎn");
		pinconv = pinconv.replace(/an4/g, "àn");
		pinconv = pinconv.replace(/an5/g, "an");
		pinconv = pinconv.replace(/ao1/g, "āo");
		pinconv = pinconv.replace(/ao2/g, "áo");
		pinconv = pinconv.replace(/ao3/g, "ǎo");
		pinconv = pinconv.replace(/ao4/g, "ào");
		pinconv = pinconv.replace(/ao5/g, "ao");
		pinconv = pinconv.replace(/ang1/g, "āng");
		pinconv = pinconv.replace(/ang2/g, "áng");
		pinconv = pinconv.replace(/ang3/g, "ǎng");
		pinconv = pinconv.replace(/ang4/g, "àng");
		pinconv = pinconv.replace(/ang5/g, "ang");
		pinconv = pinconv.replace(/e1/g, "ē");
		pinconv = pinconv.replace(/e2/g, "é");
		pinconv = pinconv.replace(/e3/g, "ě");
		pinconv = pinconv.replace(/e4/g, "è");
		pinconv = pinconv.replace(/e5/g, "e");


		pinconv = pinconv.replace(/en1/g, "ēn");
		pinconv = pinconv.replace(/en2/g, "én");
		pinconv = pinconv.replace(/en3/g, "ěn");
		pinconv = pinconv.replace(/en4/g, "èn");
		pinconv = pinconv.replace(/en5/g, "en");
		pinconv = pinconv.replace(/er1/g, "ēr");
		pinconv = pinconv.replace(/er2/g, "ér");
		pinconv = pinconv.replace(/er3/g, "ěr");
		pinconv = pinconv.replace(/er4/g, "èr");
		pinconv = pinconv.replace(/er5/g, "er");
		pinconv = pinconv.replace(/eng1/g, "ēng");
		pinconv = pinconv.replace(/eng2/g, "éng");
		pinconv = pinconv.replace(/eng3/g, "ěng");
		pinconv = pinconv.replace(/eng4/g, "èng");
		pinconv = pinconv.replace(/eng5/g, "eng");
		pinconv = pinconv.replace(/ei1/g, "ēi");
		pinconv = pinconv.replace(/ei2/g, "éi");
		pinconv = pinconv.replace(/ei3/g, "ěi");
		pinconv = pinconv.replace(/ei4/g, "èi");
		pinconv = pinconv.replace(/ei5/g, "ei");

		pinconv = pinconv.replace(/i1/g, "ī");
		pinconv = pinconv.replace(/i2/g, "í");
		pinconv = pinconv.replace(/i3/g, "ǐ");
		pinconv = pinconv.replace(/i4/g, "ì");
		pinconv = pinconv.replace(/i5/g, "i");
		pinconv = pinconv.replace(/in1/g, "īn");
		pinconv = pinconv.replace(/in2/g, "ín");
		pinconv = pinconv.replace(/in3/g, "ǐn");
		pinconv = pinconv.replace(/in4/g, "ìn");
		pinconv = pinconv.replace(/in5/g, "in");
		pinconv = pinconv.replace(/ing1/g, "īng");
		pinconv = pinconv.replace(/ing2/g, "íng");
		pinconv = pinconv.replace(/ing3/g, "ǐng");
		pinconv = pinconv.replace(/ing4/g, "ìng");
		pinconv = pinconv.replace(/ing5/g, "ing");

		pinconv = pinconv.replace(/o1/g, "ō");
		pinconv = pinconv.replace(/o2/g, "ó");
		pinconv = pinconv.replace(/o3/g, "ǒ");
		pinconv = pinconv.replace(/o4/g, "ò");
		pinconv = pinconv.replace(/o5/g, "o");
		pinconv = pinconv.replace(/ou1/g, "ōu");
		pinconv = pinconv.replace(/ou2/g, "óu");
		pinconv = pinconv.replace(/ou3/g, "ǒu");
		pinconv = pinconv.replace(/ou4/g, "òu");
		pinconv = pinconv.replace(/ou5/g, "ou");
		pinconv = pinconv.replace(/ong1/g, "ōng");
		pinconv = pinconv.replace(/ong2/g, "óng");
		pinconv = pinconv.replace(/ong3/g, "ǒng");
		pinconv = pinconv.replace(/ong4/g, "òng");
		pinconv = pinconv.replace(/ong5/g, "ong");
		
		pinconv = pinconv.replace(/u1/g, "ū");
		pinconv = pinconv.replace(/u2/g, "ú");
		pinconv = pinconv.replace(/u3/g, "ǔ");
		pinconv = pinconv.replace(/u4/g, "ù");
		pinconv = pinconv.replace(/u5/g, "u");
		pinconv = pinconv.replace(/ue1/g, "ūe");
		pinconv = pinconv.replace(/ue2/g, "úe");
		pinconv = pinconv.replace(/ue3/g, "ǔe");
		pinconv = pinconv.replace(/ue4/g, "ùe");
		pinconv = pinconv.replace(/ue5/g, "ue");
		pinconv = pinconv.replace(/ui1/g, "ūi");
		pinconv = pinconv.replace(/ui2/g, "úi");
		pinconv = pinconv.replace(/ui3/g, "ǔi");
		pinconv = pinconv.replace(/ui4/g, "ùi");
		pinconv = pinconv.replace(/ui5/g, "uie");
		pinconv = pinconv.replace(/un1/g, "ūn");
		pinconv = pinconv.replace(/un2/g, "ún");
		pinconv = pinconv.replace(/un3/g, "ǔn");
		pinconv = pinconv.replace(/un4/g, "ùn");
		pinconv = pinconv.replace(/un5/g, "un");

  return pinconv;

}
/***********************************************
* Cool DHTML tooltip script II-  Dynamic Drive DHTML code library (www.dynamicdrive.com)
* This notice MUST stay intact for legal use
* Visit Dynamic Drive at http://www.dynamicdrive.com/ for full source code
***********************************************/

var offsetfromcursorX=12 //Customize x offset of tooltip
var offsetfromcursorY=10 //Customize y offset of tooltip

var offsetdivfrompointerX=10 //Customize x offset of tooltip DIV relative to pointer image
var offsetdivfrompointerY=14 //Customize y offset of tooltip DIV relative to pointer image. Tip: Set it to (height_of_pointer_image-1).

//document.write('<div id="dhtmltooltip"></div>') //write out tooltip DIV
document.write('<div id="dhtmlpointer"></div>') //write out pointer image

var ie=document.all
var ns6=document.getElementById && !document.all
var enabletip=false
if (ie||ns6)
var tipobj=document.all? document.all["dhtmltooltip"] : document.getElementById? document.getElementById("dhtmltooltip") : ""

var pointerobj=document.all? document.all["dhtmlpointer"] : document.getElementById? document.getElementById("dhtmlpointer") : ""

function ietruebody(){
return (document.compatMode && document.compatMode!="BackCompat")? document.documentElement : document.body
}



function tip(e, event1, event2, event3, event4){
if (ns6||ie){
if (typeof thewidth!="undefined") tipobj.style.width=thewidth+"px"
if (typeof thecolor!="undefined" && thecolor!="") tipobj.style.backgroundColor=thecolor
tipobj.innerHTML='<div class="row_1" align="center">'+event3+'</div>'+'<div class="invisible_pinyin" align="center">'+event4+'</div>'+'<div class="row_3" align="center">'+check_answer(event2)+'</div>'+'<div class="row_4" align="center">'+event1+'</div>'
enabletip=true
return false
}
}


function positiontip(e){
if (enabletip){
var nondefaultpos=false
var curX=(ns6)?e.pageX : event.clientX+ietruebody().scrollLeft;
var curY=(ns6)?e.pageY : event.clientY+ietruebody().scrollTop;
//Find out how close the mouse is to the corner of the window
var winwidth=ie&&!window.opera? ietruebody().clientWidth : window.innerWidth-20
var winheight=ie&&!window.opera? ietruebody().clientHeight : window.innerHeight-20

var rightedge=ie&&!window.opera? winwidth-event.clientX-offsetfromcursorX : winwidth-e.clientX-offsetfromcursorX
var bottomedge=ie&&!window.opera? winheight-event.clientY-offsetfromcursorY : winheight-e.clientY-offsetfromcursorY

var leftedge=(offsetfromcursorX<0)? offsetfromcursorX*(-1) : -1000

//if the horizontal distance isn't enough to accomodate the width of the context menu
if (rightedge<tipobj.offsetWidth){
//move the horizontal position of the menu to the left by it's width
tipobj.style.left=curX-tipobj.offsetWidth+"px"
nondefaultpos=true
}
else if (curX<leftedge)
tipobj.style.left="5px"
else{
//position the horizontal position of the menu where the mouse is positioned
tipobj.style.left=curX+offsetfromcursorX-offsetdivfrompointerX+"px"
pointerobj.style.left=curX+offsetfromcursorX+"px"
}

//same concept with the vertical position
if (bottomedge<tipobj.offsetHeight){
tipobj.style.top=curY-tipobj.offsetHeight-offsetfromcursorY+"px"
nondefaultpos=true
}
else{
tipobj.style.top=curY+offsetfromcursorY+offsetdivfrompointerY+"px"
pointerobj.style.top=curY+offsetfromcursorY+"px"
}
tipobj.style.visibility="visible"
if (!nondefaultpos)
pointerobj.style.visibility="visible"
else
pointerobj.style.visibility="hidden"
}
}

function htip(){
if (ns6||ie){
enabletip=false
tipobj.style.visibility="hidden"
pointerobj.style.visibility="hidden"
tipobj.style.left="-1000px"
tipobj.style.backgroundColor=''
tipobj.style.width=''
}
}

document.onmousemove=positiontip
