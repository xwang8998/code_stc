#define DesInBit00 DesChangeAreaIn[0]&0x80;
#define DesInBit01 DesChangeAreaIn[0]&0x40;
#define DesInBit02 DesChangeAreaIn[0]&0x20;
#define DesInBit03 DesChangeAreaIn[0]&0x10;
#define DesInBit04 DesChangeAreaIn[0]&0x08;
#define DesInBit05 DesChangeAreaIn[0]&0x04;
#define DesInBit06 DesChangeAreaIn[0]&0x02;
#define DesInBit07 DesChangeAreaIn[0]&0x01;

#define DesInBit10 DesChangeAreaIn[1]&0x80;
#define DesInBit11 DesChangeAreaIn[1]&0x40;
#define DesInBit12 DesChangeAreaIn[1]&0x20;
#define DesInBit13 DesChangeAreaIn[1]&0x10;
#define DesInBit14 DesChangeAreaIn[1]&0x08;
#define DesInBit15 DesChangeAreaIn[1]&0x04;
#define DesInBit16 DesChangeAreaIn[1]&0x02;
#define DesInBit17 DesChangeAreaIn[1]&0x01;

#define DesInBit20 DesChangeAreaIn[2]&0x80;
#define DesInBit21 DesChangeAreaIn[2]&0x40;
#define DesInBit22 DesChangeAreaIn[2]&0x20;
#define DesInBit23 DesChangeAreaIn[2]&0x10;
#define DesInBit24 DesChangeAreaIn[2]&0x08;
#define DesInBit25 DesChangeAreaIn[2]&0x04;
#define DesInBit26 DesChangeAreaIn[2]&0x02;
#define DesInBit27 DesChangeAreaIn[2]&0x01;

#define DesInBit30 DesChangeAreaIn[3]&0x80;
#define DesInBit31 DesChangeAreaIn[3]&0x40;
#define DesInBit32 DesChangeAreaIn[3]&0x20;
#define DesInBit33 DesChangeAreaIn[3]&0x10;
#define DesInBit34 DesChangeAreaIn[3]&0x08;
#define DesInBit35 DesChangeAreaIn[3]&0x04;
#define DesInBit36 DesChangeAreaIn[3]&0x02;
#define DesInBit37 DesChangeAreaIn[3]&0x01;

#define DesInBit40 DesChangeAreaIn[4]&0x80;
#define DesInBit41 DesChangeAreaIn[4]&0x40;
#define DesInBit42 DesChangeAreaIn[4]&0x20;
#define DesInBit43 DesChangeAreaIn[4]&0x10;
#define DesInBit44 DesChangeAreaIn[4]&0x08;
#define DesInBit45 DesChangeAreaIn[4]&0x04;
#define DesInBit46 DesChangeAreaIn[4]&0x02;
#define DesInBit47 DesChangeAreaIn[4]&0x01;

#define DesInBit50 DesChangeAreaIn[5]&0x80;
#define DesInBit51 DesChangeAreaIn[5]&0x40;
#define DesInBit52 DesChangeAreaIn[5]&0x20;
#define DesInBit53 DesChangeAreaIn[5]&0x10;
#define DesInBit54 DesChangeAreaIn[5]&0x08;
#define DesInBit55 DesChangeAreaIn[5]&0x04;
#define DesInBit56 DesChangeAreaIn[5]&0x02;
#define DesInBit57 DesChangeAreaIn[5]&0x01;

#define DesInBit60 DesChangeAreaIn[6]&0x80;
#define DesInBit61 DesChangeAreaIn[6]&0x40;
#define DesInBit62 DesChangeAreaIn[6]&0x20;
#define DesInBit63 DesChangeAreaIn[6]&0x10;
#define DesInBit64 DesChangeAreaIn[6]&0x08;
#define DesInBit65 DesChangeAreaIn[6]&0x04;
#define DesInBit66 DesChangeAreaIn[6]&0x02;
#define DesInBit67 DesChangeAreaIn[6]&0x01;

#define DesInBit70 DesChangeAreaIn[7]&0x80;
#define DesInBit71 DesChangeAreaIn[7]&0x40;
#define DesInBit72 DesChangeAreaIn[7]&0x20;
#define DesInBit73 DesChangeAreaIn[7]&0x10;
#define DesInBit74 DesChangeAreaIn[7]&0x08;
#define DesInBit75 DesChangeAreaIn[7]&0x04;
#define DesInBit76 DesChangeAreaIn[7]&0x02;
#define DesInBit77 DesChangeAreaIn[7]&0x01;









#define DesKey64To56() {\
	 DesOutBit04=DesInBit70;DesOutBit05=DesInBit60;\
	 DesOutBit06=DesInBit50;DesOutBit07=DesInBit40;\
	 DesOutBit10=DesInBit30;DesOutBit11=DesInBit20;\
	 DesOutBit12=DesInBit10;DesOutBit13=DesInBit00;\
	 DesOutBit14=DesInBit71;DesOutBit15=DesInBit61;\
	 DesOutBit16=DesInBit51;DesOutBit17=DesInBit41;\
	 DesOutBit20=DesInBit31;DesOutBit21=DesInBit21;\
	 DesOutBit22=DesInBit11;DesOutBit23=DesInBit01;\
	 DesOutBit24=DesInBit72;DesOutBit25=DesInBit62;\
	 DesOutBit26=DesInBit52;DesOutBit27=DesInBit42;\
	 DesOutBit30=DesInBit32;DesOutBit31=DesInBit22;\
	 DesOutBit32=DesInBit12;DesOutBit33=DesInBit02;\
	 DesOutBit34=DesInBit73;DesOutBit35=DesInBit63;\
	 DesOutBit36=DesInBit53;DesOutBit37=DesInBit43;\
	\
	 DesOutBit44=DesInBit76;DesOutBit45=DesInBit66;\
	 DesOutBit46=DesInBit56;DesOutBit47=DesInBit46;\
	 DesOutBit50=DesInBit36;DesOutBit51=DesInBit26;\
	 DesOutBit52=DesInBit16;DesOutBit53=DesInBit06;\
	 DesOutBit54=DesInBit75;DesOutBit55=DesInBit65;\
	 DesOutBit56=DesInBit55;DesOutBit57=DesInBit45;\
	 DesOutBit60=DesInBit35;DesOutBit61=DesInBit25;\
	 DesOutBit62=DesInBit15;DesOutBit63=DesInBit05;\
	 DesOutBit64=DesInBit74;DesOutBit65=DesInBit64;\
	 DesOutBit66=DesInBit54;DesOutBit67=DesInBit44;\
	 DesOutBit70=DesInBit34;DesOutBit71=DesInBit24;\
	 DesOutBit72=DesInBit14;DesOutBit73=DesInBit04;\
	 DesOutBit74=DesInBit33;DesOutBit75=DesInBit23;\
	 DesOutBit76=DesInBit13;DesOutBit77=DesInBit03;\
}

#define DesKey56To48() {\
	 DesOutBit00=DesInBit21;DesOutBit01=DesInBit24;\
	 DesOutBit02=DesInBit16;DesOutBit03=DesInBit33;\
	 DesOutBit04=DesInBit04;DesOutBit05=DesInBit10;\
	 DesOutBit06=DesInBit06;DesOutBit07=DesInBit37;\
	 DesOutBit10=DesInBit22;DesOutBit11=DesInBit11;\
	 DesOutBit12=DesInBit30;DesOutBit13=DesInBit15;\
	 DesOutBit14=DesInBit32;DesOutBit15=DesInBit26;\
	 DesOutBit16=DesInBit17;DesOutBit17=DesInBit07;\
	 DesOutBit20=DesInBit35;DesOutBit21=DesInBit13;\
	 DesOutBit22=DesInBit23;DesOutBit23=DesInBit12;\
	 DesOutBit24=DesInBit36;DesOutBit25=DesInBit27;\
	 DesOutBit26=DesInBit20;DesOutBit27=DesInBit05;\
	\
	 DesOutBit30=DesInBit60;DesOutBit31=DesInBit73;\
	 DesOutBit32=DesInBit46;DesOutBit33=DesInBit54;\
	 DesOutBit34=DesInBit66;DesOutBit35=DesInBit76;\
	 DesOutBit36=DesInBit45;DesOutBit37=DesInBit57;\
	 DesOutBit40=DesInBit72;DesOutBit41=DesInBit64;\
	 DesOutBit42=DesInBit50;DesOutBit43=DesInBit67;\
	 DesOutBit44=DesInBit63;DesOutBit45=DesInBit70;\
	 DesOutBit46=DesInBit56;DesOutBit47=DesInBit77;\
	 DesOutBit50=DesInBit51;DesOutBit51=DesInBit74;\
	 DesOutBit52=DesInBit65;DesOutBit53=DesInBit61;\
	 DesOutBit54=DesInBit71;DesOutBit55=DesInBit53;\
	 DesOutBit56=DesInBit44;DesOutBit57=DesInBit47;\
}

#define DesDat64IP() {\
	 DesOutBit00=DesInBit71;DesOutBit01=DesInBit61;\
	 DesOutBit02=DesInBit51;DesOutBit03=DesInBit41;\
	 DesOutBit04=DesInBit31;DesOutBit05=DesInBit21;\
	 DesOutBit06=DesInBit11;DesOutBit07=DesInBit01;\
	 DesOutBit10=DesInBit73;DesOutBit11=DesInBit63;\
	 DesOutBit12=DesInBit53;DesOutBit13=DesInBit43;\
	 DesOutBit14=DesInBit33;DesOutBit15=DesInBit23;\
	 DesOutBit16=DesInBit13;DesOutBit17=DesInBit03;\
	 DesOutBit20=DesInBit75;DesOutBit21=DesInBit65;\
	 DesOutBit22=DesInBit55;DesOutBit23=DesInBit45;\
	 DesOutBit24=DesInBit35;DesOutBit25=DesInBit25;\
	 DesOutBit26=DesInBit15;DesOutBit27=DesInBit05;\
	 DesOutBit30=DesInBit77;DesOutBit31=DesInBit67;\
	 DesOutBit32=DesInBit57;DesOutBit33=DesInBit47;\
	 DesOutBit34=DesInBit37;DesOutBit35=DesInBit27;\
	 DesOutBit36=DesInBit17;DesOutBit37=DesInBit07;\
	\
	 DesOutBit40=DesInBit70;DesOutBit41=DesInBit60;\
	 DesOutBit42=DesInBit50;DesOutBit43=DesInBit40;\
	 DesOutBit44=DesInBit30;DesOutBit45=DesInBit20;\
	 DesOutBit46=DesInBit10;DesOutBit47=DesInBit00;\
	 DesOutBit50=DesInBit72;DesOutBit51=DesInBit62;\
	 DesOutBit52=DesInBit52;DesOutBit53=DesInBit42;\
	 DesOutBit54=DesInBit32;DesOutBit55=DesInBit22;\
	 DesOutBit56=DesInBit12;DesOutBit57=DesInBit02;\
	 DesOutBit60=DesInBit74;DesOutBit61=DesInBit64;\
	 DesOutBit62=DesInBit54;DesOutBit63=DesInBit44;\
	 DesOutBit64=DesInBit34;DesOutBit65=DesInBit24;\
	 DesOutBit66=DesInBit14;DesOutBit67=DesInBit04;\
	 DesOutBit70=DesInBit76;DesOutBit71=DesInBit66;\
	 DesOutBit72=DesInBit56;DesOutBit73=DesInBit46;\
	 DesOutBit74=DesInBit36;DesOutBit75=DesInBit26;\
	 DesOutBit76=DesInBit16;DesOutBit77=DesInBit06;\
}

#define DesDat64IP_R() {\
	 DesOutBit00=DesInBit47;DesOutBit01=DesInBit07;\
	 DesOutBit02=DesInBit57;DesOutBit03=DesInBit17;\
	 DesOutBit04=DesInBit67;DesOutBit05=DesInBit27;\
	 DesOutBit06=DesInBit77;DesOutBit07=DesInBit37;\
	 DesOutBit10=DesInBit46;DesOutBit11=DesInBit06;\
	 DesOutBit12=DesInBit56;DesOutBit13=DesInBit16;\
	 DesOutBit14=DesInBit66;DesOutBit15=DesInBit26;\
	 DesOutBit16=DesInBit76;DesOutBit17=DesInBit36;\
	 DesOutBit20=DesInBit45;DesOutBit21=DesInBit05;\
	 DesOutBit22=DesInBit55;DesOutBit23=DesInBit15;\
	 DesOutBit24=DesInBit65;DesOutBit25=DesInBit25;\
	 DesOutBit26=DesInBit75;DesOutBit27=DesInBit35;\
	 DesOutBit30=DesInBit44;DesOutBit31=DesInBit04;\
	 DesOutBit32=DesInBit54;DesOutBit33=DesInBit14;\
	 DesOutBit34=DesInBit64;DesOutBit35=DesInBit24;\
	 DesOutBit36=DesInBit74;DesOutBit37=DesInBit34;\
	\
	 DesOutBit40=DesInBit43;DesOutBit41=DesInBit03;\
	 DesOutBit42=DesInBit53;DesOutBit43=DesInBit13;\
	 DesOutBit44=DesInBit63;DesOutBit45=DesInBit23;\
	 DesOutBit46=DesInBit73;DesOutBit47=DesInBit33;\
	 DesOutBit50=DesInBit42;DesOutBit51=DesInBit02;\
	 DesOutBit52=DesInBit52;DesOutBit53=DesInBit12;\
	 DesOutBit54=DesInBit62;DesOutBit55=DesInBit22;\
	 DesOutBit56=DesInBit72;DesOutBit57=DesInBit32;\
	 DesOutBit60=DesInBit41;DesOutBit61=DesInBit01;\
	 DesOutBit62=DesInBit51;DesOutBit63=DesInBit11;\
	 DesOutBit64=DesInBit61;DesOutBit65=DesInBit21;\
	 DesOutBit66=DesInBit71;DesOutBit67=DesInBit31;\
	 DesOutBit70=DesInBit40;DesOutBit71=DesInBit00;\
	 DesOutBit72=DesInBit50;DesOutBit73=DesInBit10;\
	 DesOutBit74=DesInBit60;DesOutBit75=DesInBit20;\
	 DesOutBit76=DesInBit70;DesOutBit77=DesInBit30;\
}

#define DesDat32To48() {\
	 DesOutBit00=DesInBit37;DesOutBit01=DesInBit00;\
	 DesOutBit02=DesInBit01;DesOutBit03=DesInBit02;\
	 DesOutBit04=DesInBit03;DesOutBit05=DesInBit04;\
	 DesOutBit06=DesInBit03;DesOutBit07=DesInBit04;\
	 DesOutBit10=DesInBit05;DesOutBit11=DesInBit06;\
	 DesOutBit12=DesInBit07;DesOutBit13=DesInBit10;\
	 DesOutBit14=DesInBit07;DesOutBit15=DesInBit10;\
	 DesOutBit16=DesInBit11;DesOutBit17=DesInBit12;\
	 DesOutBit20=DesInBit13;DesOutBit21=DesInBit14;\
	 DesOutBit22=DesInBit13;DesOutBit23=DesInBit14;\
	 DesOutBit24=DesInBit15;DesOutBit25=DesInBit16;\
	 DesOutBit26=DesInBit17;DesOutBit27=DesInBit20;\
	 DesOutBit30=DesInBit17;DesOutBit31=DesInBit20;\
	 DesOutBit32=DesInBit21;DesOutBit33=DesInBit22;\
	 DesOutBit34=DesInBit23;DesOutBit35=DesInBit24;\
	 DesOutBit36=DesInBit23;DesOutBit37=DesInBit24;\
	 DesOutBit40=DesInBit25;DesOutBit41=DesInBit26;\
	 DesOutBit42=DesInBit27;DesOutBit43=DesInBit30;\
	 DesOutBit44=DesInBit27;DesOutBit45=DesInBit30;\
	 DesOutBit46=DesInBit31;DesOutBit47=DesInBit32;\
	 DesOutBit50=DesInBit33;DesOutBit51=DesInBit34;\
	 DesOutBit52=DesInBit33;DesOutBit53=DesInBit34;\
	 DesOutBit54=DesInBit35;DesOutBit55=DesInBit36;\
	 DesOutBit56=DesInBit37;DesOutBit57=DesInBit00;\
}
/*---*/
#define DesDatBitSwap() {\
	\
	 DesOutBit02=DesInBit00;DesOutBit03=DesInBit05;\
	 DesOutBit04=DesInBit01;DesOutBit05=DesInBit02;\
	 DesOutBit06=DesInBit03;DesOutBit07=DesInBit04;\
	\
	 DesOutBit12=DesInBit06;DesOutBit13=DesInBit13;\
	 DesOutBit14=DesInBit07;DesOutBit15=DesInBit10;\
	 DesOutBit16=DesInBit11;DesOutBit17=DesInBit12;\
	\
	 DesOutBit22=DesInBit14;DesOutBit23=DesInBit21;\
	 DesOutBit24=DesInBit15;DesOutBit25=DesInBit16;\
	 DesOutBit26=DesInBit17;DesOutBit27=DesInBit20;\
	\
	 DesOutBit32=DesInBit22;DesOutBit33=DesInBit27;\
	 DesOutBit34=DesInBit23;DesOutBit35=DesInBit24;\
	 DesOutBit36=DesInBit25;DesOutBit37=DesInBit26;\
	\
	 DesOutBit42=DesInBit30;DesOutBit43=DesInBit35;\
	 DesOutBit44=DesInBit31;DesOutBit45=DesInBit32;\
	 DesOutBit46=DesInBit33;DesOutBit47=DesInBit34;\
	\
	 DesOutBit52=DesInBit36;DesOutBit53=DesInBit43;\
	 DesOutBit54=DesInBit37;DesOutBit55=DesInBit40;\
	 DesOutBit56=DesInBit41;DesOutBit57=DesInBit42;\
	\
	 DesOutBit62=DesInBit44;DesOutBit63=DesInBit51;\
	 DesOutBit64=DesInBit45;DesOutBit65=DesInBit46;\
	 DesOutBit66=DesInBit47;DesOutBit67=DesInBit50;\
	\
	 DesOutBit72=DesInBit52;DesOutBit73=DesInBit57;\
	 DesOutBit74=DesInBit53;DesOutBit75=DesInBit54;\
	 DesOutBit76=DesInBit55;DesOutBit77=DesInBit56;\
}

#define DesDat32To32() {\
	DesOutBit00=DesInBit17;DesOutBit01=DesInBit06;\
	DesOutBit02=DesInBit23;DesOutBit03=DesInBit24;\
	DesOutBit04=DesInBit34;DesOutBit05=DesInBit13;\
	DesOutBit06=DesInBit33;DesOutBit07=DesInBit20;\
	DesOutBit10=DesInBit00;DesOutBit11=DesInBit16;\
	DesOutBit12=DesInBit26;DesOutBit13=DesInBit31;\
	DesOutBit14=DesInBit04;DesOutBit15=DesInBit21;\
	DesOutBit16=DesInBit36;DesOutBit17=DesInBit11;\
	DesOutBit20=DesInBit01;DesOutBit21=DesInBit07;\
	DesOutBit22=DesInBit27;DesOutBit23=DesInBit15;\
	DesOutBit24=DesInBit37;DesOutBit25=DesInBit32;\
	DesOutBit26=DesInBit02;DesOutBit27=DesInBit10;\
	DesOutBit30=DesInBit22;DesOutBit31=DesInBit14;\
	DesOutBit32=DesInBit35;DesOutBit33=DesInBit05;\
	DesOutBit34=DesInBit25;DesOutBit35=DesInBit12;\
	DesOutBit36=DesInBit03;DesOutBit37=DesInBit30;\
}