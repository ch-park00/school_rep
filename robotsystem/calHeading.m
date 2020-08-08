%%
function [heading]=calHeading(utmX,utmY,flag)

persistent pre_utm_x pre_utm_y
persistent pre_utm_x2 pre_utm_y2
persistent firstrun

if isempty(firstrun)
    pre_utm_x=0;
    pre_utm_y=0;
    pre_utm_x2=0;
    pre_utm_y2=0;
    firstrun=1;
end

utmX=utmX*pi/180;
utmY=utmY*pi/180;

if flag==1
    preX=pre_utm_x;
    preY=pre_utm_y;
    pre_utm_x=utmX;
    pre_utm_y=utmY;
    
else
    preX=pre_utm_x2;
    preY=pre_utm_y2;
    
    pre_utm_x2=utmX;
    pre_utm_y2=utmY;
end

XX=cos(preX)*sin(utmX)-sin(preX)*cos(utmX)*cos(utmY-preY);
YY=sin(utmY-preY)*cos(utmX);
heading=atan2(YY,XX);
end