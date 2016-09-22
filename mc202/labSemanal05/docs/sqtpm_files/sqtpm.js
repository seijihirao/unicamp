
// This file is part of sqtpm v6.

function login() { 
    if (document.sqtpm.uid.value == null || document.sqtpm.uid.value == "") { 
	document.sqtpm.uid.focus(); 
    }
    else if (document.sqtpm.pwd.value == null || document.sqtpm.pwd.value == "") { 
	document.sqtpm.pwd.focus(); 
    }
    else { 
	document.sqtpm.action.value = 'in'; 
	document.sqtpm.submit(); 
    }
}


function enterh(e,name) {
    if (e.which == 13) { 
	if (name == "u") { 
	    document.sqtpm.pwd.focus(); 
	} 
	else { 
	    login();
	} 
    }
}


function about() { 
    document.sqtpm.action.value = 'about';
    document.sqtpm.submit(); 
}


function wrap(action,arg1,arg2) { 
    document.sqtpm.action.value = action;
    document.sqtpm.arg1.value = arg1;
    document.sqtpm.arg2.value = arg2;
    document.sqtpm.submit(); 
}


function toggleDiv(divid){
    var e = document.getElementById(divid);
    e.style.display = (e.style.display == "none" ? "block" : "none");
}


// Pop-up filling functions adapted from those publicized at
// http://bdhacker.wordpress.com/2009/11/21/adding-dropdown-country-state-\
// list-dynamically-into-your-html-form-by-javascript/

function fill_langs(assignId,langId) {
    var langElem = document.getElementById(langId);
    langElem.length = 0;
    langElem.selectedIndex = 0;
    
    var assign = document.getElementById(assignId).selectedIndex;
    var tags = language_tags[assign].split("|");
    var labels = language_labels[assign].split("|");
    
    for (var i=0; i<tags.length; i++) {
	langElem.options[i] = new Option(labels[i],tags[i]);
    }
}


function fill_assigns(assignId,langId) {
    var assignElem = document.getElementById(assignId);
    assignElem.length = 0;
    assignElem.selectedIndex = 0;

    assignElem.options[0] = new Option("selecione...","0");
    
    for (var i=0; i<assignments.length; i++) {
  	assignElem.options[i+1] = new Option(assignments[i],assignments[i]);
    }
}

