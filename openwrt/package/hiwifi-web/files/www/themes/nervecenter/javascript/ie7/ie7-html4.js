/* IE7 version 0.7.3 (alpha) 2004/09/18 */
if(window.IE7)IE7.addModule("ie7-html4",function(){if(isHTML)HTMLFixes=new function(){var fixes=[];function fix(element){var fixedElement=document.createElement("<HTML:"+element.outerHTML.slice(1));if(element.outerHTML.slice(-2)!="/>"){var endTag="</"+element.tagName+">",nextSibling;while((nextSibling=element.nextSibling)&&nextSibling.outerHTML!=endTag){element.parentNode.removeChild(nextSibling);fixedElement.appendChild(nextSibling)}if(nextSibling)element.parentNode.removeChild(nextSibling)}element.parentNode.replaceChild(fixedElement,element);return fixedElement};this.add=function(){push(fixes,arguments)};this.apply=function(){try{if(appVersion>5)document.namespaces.add("HTML","http://www.w3.org/1999/xhtml")}catch(ignore){}finally{for(var i=0;i<fixes.length;i++){var elements=cssQuery(fixes[i][0]);for(var j=0;j<elements.length;j++)fixes[i][1](elements[j])}}};this.add("label",function(element){if(!element.htmlFor){var input=cssQuery("input,select,textarea",element)[0];if(input){if(!input.id)input.id=input.uniqueID;element.htmlFor=input.id}}});this.add("abbr",function(element){fix(element);delete cssCache[" abbr"]});this.add("button,input",function(element){if(element.tagName=="BUTTON"){var match=element.outerHTML.match(/ value="([^"]*)"/i);element.runtimeStyle.value=(match)?match[1]:""}if(element.type=="submit"){addEventHandler(element,"onclick",function(){element.runtimeStyle.clicked=true;setTimeout("document.all."+element.uniqueID+".runtimeStyle.clicked=false",1)})}});this.add("form",function(element){var UNSUCCESSFUL=/^(submit|reset|button)$/;addEventHandler(element,"onsubmit",function(){for(var i=0;i<element.length;i++){if(UNSUCCESSFUL.test(element[i].type)&&!element[i].disabled&&!element[i].runtimeStyle.clicked){element[i].disabled=true;setTimeout("document.all."+element[i].uniqueID+".disabled=false",1)}else if(element[i].tagName=="BUTTON"&&element[i].type=="submit"){setTimeout("document.all."+element[i].uniqueID+".value='"+element[i].value+"'",1);element[i].value=element[i].runtimeStyle.value}}})})}},true);