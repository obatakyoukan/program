// JavaScript Document
// (c)TheDesignum
// var OS = $.os.name;
// var UA = $.browser.name;

var aoj = {
	init: function() {
	},
	dominit: function() {
		$('#cfBlock').hide();
		//chrome frame check for IE
		//if($.browser.name == 'msie') this.frameChecker();
		$(window).resize(function() {aoj.resize()});
		this.navFunc();
		this.tableFunc();
		this.resize();
		if($('#visual').length) this.sliderFunc();
		twitter.init();
	},
	frameChecker: function() {
		CFInstall.check({
			node: "cfBlock",
			oninstall: function() {
				$('#cfBlock').hide();
			},
			onmissing: function() {
				$('#cfBlock').show();
			}
		});
	},
	tableFunc: function() {
		$('table tr td:last-child').each(function(){
			//$(this).css('border-right','none');
		});
	        $('.tablewrapper tr td:first-child').each(function(){
                    $(this).css('border-left','1px solid #dddddd'); /* 2015/11/15 */
                });
		$('table tr.dat:odd').css('background-color','#F7FCFE');
		$('table tr.dat').each(function(){
			$(this).mouseenter(function(){
				$(this).css('background-color','#DEE8FF');
			});
			$(this).mouseleave(function(){
				$('table tr.dat:even').css('background-color','#FFFFFF');
				$('table tr.dat:odd').css('background-color','#F7FCFE');
			});
		});
		if($('#tableActivity').length) {
			var setTableSize = [510,120,100,65,190,45];
			for(i=1; i <= 5; i++) {
				$('#tableActivity tr td:nth-child('+i+')').css('width', setTableSize[i]);
			}
		}	else if($('#tableRanking').length) {
			ranking.init();
		}
	},
	navFunc: function() {
    $(window).bind('scroll',function(){
			var scrollPos = $(window).scrollTop();
			if(scrollPos > 45) $('#nav').css({'top': 0});
			else $('#nav').css({'top': 45 - scrollPos});
		});
		$('#menuPagetop').click(function(){
			$('html,body').animate({scrollTop: 0}, {queue: false, easing: "easeOutQuad"});
		});
		$('#nav #menu .trigger').each(function(i) {
			$(this).hover(
				function(){
					var menuPos = $(this).position();
					var targetTree = i + 1;
					$('#nav #tree').attr('data-target',targetTree).css({'margin': '40px 0px 0px ' + menuPos.left + 'px'}).show();
					$('#nav #tree .dat').hide();
					$('#nav #tree .dat:nth-child('+targetTree+')').show();
					$(this).addClass('active');
				},
				function(){
					$(this).removeClass('active');
					$('#nav #tree').hide();
				}
			);
		});		
                // not used
		$('#nav #tree').hover(
			function() {
				var targetTrigger = 2 * $('#nav #tree').attr('data-target') + 1; // 2n+1				
				$(this).show();
				$('#nav #menu a:nth-child('+targetTrigger+')').addClass('active');
			},
			function(){
				$(this).hide();
				$('#nav #menu .trigger').removeClass('active');
			}
		);
	},
	sliderFunc: function() {
		$('#switcher .switch').each(function(i){
			if(i==0) $(this).addClass('active');
			$(this).mouseover(function() {
				var slidePos = '-' + (i * 298);
				$('#switcher .switch').removeClass('active');
				$(this).addClass('active');
				$('#slider .slide:first-child').animate({'margin-top': slidePos + 'px'}, {queue: false, easing: "easeOutQuad"});
		  });
		});
	},
	resize: function() {
		var offset = $('#lang').offset();
		$('#logo').css('left',offset.left);
	}
}

var page = { pagePer: 10, pageNow: 1, datCount: 0, pageTotal: 0}
var ranking = {
	init: function(){
		var	datStart = (page.pageNow - 1)*page.pagePer;
		var datEnd = page.pageNow*page.pagePer;
		$('table tr.dat').each(function(j){
			if(j>=datStart && j<datEnd) {
				$(this).show();
			} else {
				$(this).hide();
			}
			page.datCount++;
		});
		page.pageTotal = Math.ceil(page.datCount/page.pagePer);
	    // add 2011.07.20
	if($.cookie('the_cookie')) {
			page.pagePer = $.cookie('the_cookie');
			$('.per-page').each(function(){
				if($(this).attr('data-num') == page.pagePer) $(this).addClass('setPer');
				else $(this).removeClass('setPer');
			});
			ranking.pageFunc();
		};


		$('.pageTotal').text(page.pageTotal);
		$('.per-page').each(function(){
			$(this).click(function(){
				$('.per-page').removeClass('setPer');
				$(this).addClass('setPer');
				page.pagePer = $(this).attr('data-num');
	// add 2011.07.20
				$.cookie('the_cookie', page.pagePer, { expires: 14 });

				page.pageNow = 1;
				page.pageTotal = Math.ceil(page.datCount/page.pagePer);
				$('.pageNow').attr('value',page.pageNow);
				$('.pageTotal').text(page.pageTotal);
				ranking.pageFunc();
			});
		});
		$('.pageNext').click(function(){
			var pageCount = parseInt($('.pageNow').attr('value')) + 1;
			if(pageCount <= page.pageTotal){
				$('.pageNow').attr('value',pageCount);
				ranking.pageFunc();
			}
		});
		$('.pagePrev').click(function(){
			var pageCount = parseInt($('.pageNow').attr('value')) - 1;
			if(pageCount > 0) {
				$('.pageNow').attr('value',pageCount);
				ranking.pageFunc();
			}
		});
		$('.pageNow').each(function(){
			$(this).change(function(){
				var str = $(this).attr('value');
				console.log('%s',str);
				if(str.match(/[^0-9]+/)) {
					$('.pageNow').attr('value',1);
					pageNow = 1;
				} else if(str > page.pageTotal) {
					$('.pageNow').attr('value',page.pageTotal);
					pageNow = page.pageTotal;
				} else {
					pageNow = $(this).attr('value');
					$('.pageNow').attr('value',pageNow);
				}
				ranking.pageFunc();
			});
		});
	},
	pageFunc: function() {
		page.pageNow = $('#pageNow').attr('value');
		var datStart = (page.pageNow - 1)*page.pagePer;
		var datEnd = page.pageNow*page.pagePer;
		$('table tr.dat').each(function(j){
			if(j>=datStart && j<datEnd) $(this).show();
			else	$(this).hide();
		});
	}
}

var twitter = {
	init: function() {
		var account = "aizu_oj";
		var twitDat = "http://api.twitter.com/1/statuses/user_timeline/"+account+".json?count=1&callback=?";
		this.twitFunc(twitDat);
	},
	twitFunc: function jsonTwit(twitDat){
		$.getJSON(twitDat, function(dat){
			var profile = dat[0].user.profile_image_url;
			var name = dat[0].user.screen_name;
			var source = dat[0].source;
			$('#twitProfile').attr('src',profile);
			$('#twitName').html(name);
			$('#twitSource').html(' from ' + source);

			$.each(dat,function(i,item){
				var comment = item.text;
   		 	var dt = item.created_at.split(" ");
    		var date =  dt[0] + " " + dt[2] + " " + dt[1] + " " + dt[3] + " " + dt[4] + " " + dt[5];
  		  var datAt = new Date(date);
				var datNow = new Date();
				var delta = datNow.getTime()-datAt.getTime();
				//console.log('%s',delta);
				delta = delta / (60 * 60 * 1000);
				var deltaMin = delta * 60;
				if(deltaMin < 60) {
					delta = parseInt(delta * 60);
					if(delta == 1) {
						$('#twitTime').text('a minute ago');
					} else {
						$('#twitTime').text(delta + ' minutes ago');
					};
				} else if (delta > 23) {
					delta = parseInt(delta / 24);
					if(delta == 1) {
						$('#twitTime').text('yesterday');
					} else {
						$('#twitTime').text(delta + ' days ago');
					};
				} else {
					delta = parseInt(delta);
					if(delta == 1) {
						$('#twitTime').text('an hour ago');
					} else {
						$('#twitTime').text(delta + ' hours ago');
					};
				}
				$('#twitComment').html(comment);
			});
		},"json");
	}
}



$(document).ready(function(){ 
    aoj.dominit() ;

});
window.onload = function() {
	aoj.init();
    showSchedule();
};