clc;
clear; 
close all; 
ha = axes('Units', 'pixels', 'Position', [60, 50, 400, 400]); 
axis( [-600 600 -600 600] )   
set(gca,'ylim',[-600 600],'xlim',[-600 600])
xlabel('x');
ylabel('y');
opt.fontname = 'helvetica';
opt.fontsize = 8;
centeraxes(gca,opt);
hold on;
ptgrid = uicontrol('Style', 'pushbutton', ...
    'String', '网格', 'Position', [480, 150, 60, 30], 'Callback', 'grid'); 
btncla = uicontrol('Style', 'pushbutton', ...
    'String', '清除', 'Position', [480, 110, 60, 30], 'Callback', 'cla');
hpop = uicontrol(gcf,'Style','popupmenu',...
    'String', 'DDA|Bresenham|中点圆|中点椭圆',...
'Position', [480 190 60 30],...
'Callback', '@plot_sin');
x0 = uicontrol('Style', 'text', ...
    'String', 'x', 'Position', [480, 380, 20, 20]);
ex0=uicontrol('Style', 'edit', ...
   'Tag','ex0', 'String', '', 'Position', [480, 360, 25, 20]);
y0 = uicontrol('Style', 'text', ...
    'String', 'y', 'Position', [510, 380, 20, 20]);
ey0=uicontrol('Style', 'edit', ...
   'Tag','ey0', 'String', '', 'Position', [510, 360, 25, 20]);
x1 = uicontrol('Style', 'text', ...
    'String', 'x1', 'Position', [480, 340, 20, 20]);
ex1=uicontrol('Style', 'edit', ...
    'Tag','ex1','String', '', 'Position', [480, 320, 25, 20]);
y1 = uicontrol('Style', 'text', ...
    'String', 'y1', 'Position', [510, 340, 20, 20]);
ey1=uicontrol('Style', 'edit', ...
   'Tag','ey1', 'String', '', 'Position', [510, 320, 25, 20]);
r = uicontrol('Style', 'text', ...
    'String', 'r', 'Position', [480, 300, 20, 20]);
er=uicontrol('Style', 'edit', ...
    'Tag','er','String', '', 'Position', [480, 280, 25, 20]);
a = uicontrol('Style', 'text', ...
    'String', 'a', 'Position', [480, 260, 20, 20]);
ea=uicontrol('Style', 'edit', ...
   'Tag','ea', 'String', '', 'Position', [480, 240, 25, 20]);
b = uicontrol('Style', 'text', ...
    'String', 'b', 'Position', [510, 260, 20, 20]);
eb=uicontrol('Style', 'edit', ...
   'Tag','eb', 'String', '', 'Position', [510, 240, 25, 20]);
label=uicontrol('Style','text','String','制作人:白思雨','Position',[600,40, 100, 30]);
hpop.Callback = @plot_sin;   


function plot_sin(hpop,source, callbackdata)
X0=findobj('Tag', 'ex0');
Y0=findobj('Tag', 'ey0');
X1=findobj('Tag', 'ex1');
Y1=findobj('Tag', 'ey1');
R0=findobj('Tag', 'er');
A0=findobj('Tag', 'ea');
B0=findobj('Tag', 'eb');
val = get(hpop,'Value');
if val == 1
    DDA(str2num(X0.String),str2num(Y0.String),str2num(X1.String),str2num(Y1.String));
elseif val == 2
    BresenhamLine(str2num(X0.String),str2num(Y0.String),str2num(X1.String),str2num(Y1.String));
elseif val == 3
Bresenhamcircle(str2num(X0.String),str2num(Y0.String),str2num(R0.String));
elseif val == 4
Bresenhamellipse(str2num(A0.String),str2num(B0.String));
end
end



