function out = centeraxes(ax,opt)
if nargin < 2,
    fontsize = get(ax,'FontSize');
    fontname = get(ax,'FontName');
end
if nargin < 1,
    ax = gca;
end
if nargin == 2,
    if isfield(opt,'fontsize'),
        fontsize = opt.fontsize;
    else
        fontsize = get(ax,'FontSize');
    end;
    if isfield(opt,'fontname'),
        fontname = opt.fontname;
    else
        fontname = get(ax,'FontName');
    end
end
axes(ax);
set(gcf,'color',[1 1 1]);
xtext = get(get(ax,'xlabel'),'string');
ytext = get(get(ax,'ylabel'),'string');
xlim = 1.1*get(ax,'xlim');
ylim = 1.1*get(ax,'ylim');
set(ax,'xlim',xlim);
set(ax,'ylim',ylim);
if xlim(1)>0,
    xlim(1) = 0;
end
if ylim(1)>0,
    ylim(1) = 0;
end
if xlim(2) < 0,
    xlim(2) = 0;
end
if ylim(2) < 0,
    ylim(2) = 0;
end;
set(ax,'xlim',xlim,'ylim',ylim);
axpos = get(ax,'position');
figpos = get(gcf,'position');
if (strcmp(get(gcf,'Units'),'normalized')) 
    screensize = get( 0, 'ScreenSize' ); 
    figpos = figpos.*screensize; 
end
aspectratio = axpos(4) / (axpos(3));
xsize = xlim(2) - xlim(1);
ysize = ylim(2) - ylim(1);
xticksize = ysize/figpos(4)*12;
yticksize = xsize*aspectratio/figpos(3)*12;
ytick = get(ax,'YTick');
xtick = get(ax,'XTick');
xticklab = get(ax,'XTickLabel');
yticklab = get(ax,'YTickLabel');
yax = line([0; 0],[ylim(1)-1; ylim(2)]);
xax = line([xlim(1); xlim(2)],[0; 0]);
set(xax,'color',[0 0 0])
set(yax,'color',[0 0 0])
for k = 1:length(xtick),
    newxtick(k) = line([xtick(k); xtick(k)],[-xticksize/2; xticksize/2]);
    if (xtick(k)~=0),
        newxticklab(k) = text(xtick(k),-1.5*xticksize, strtrim(xticklab(k,:)));
        set(newxticklab(k),'HorizontalAlignment','center',...
            'Fontsize',fontsize,'FontName',fontname);
    end
end
set(newxtick,'color',[0 0 0]);
for k = 1:length(ytick),
    newytick(k) = line([-yticksize/2; yticksize/2],[ytick(k); ytick(k)]);
    if (ytick(k)~=0),
        newyticklab(k) = text(-.8*yticksize,ytick(k), yticklab(k,:));
        set(newyticklab(k),'HorizontalAlignment','right',...
            'FontSize',fontsize,'FontName',fontname);
    end
end
set(newytick,'color',[0 0 0]);
newxlabel = text(xlim(2),-1.5*xticksize,xtext);
set(newxlabel,'HorizontalAlignment','center',...
    'FontWeight','demi','FontSize',fontsize+2,'FontName',fontname);
newylabel = text(-yticksize,ylim(2)*1.02,ytext);
set(newylabel,'HorizontalAlignment','right','VerticalAlignment','top',...
    'FontWeight','demi','FontSize',fontsize+2,'FontName',fontname);
x = [0; -yticksize/4; yticksize/4];
y = [ylim(2); ylim(2)-xticksize; ylim(2)-xticksize];
patch(x,y,[0 0 0])
x = [xlim(2); xlim(2)-yticksize; xlim(2)-yticksize];
y = [0; xticksize/4; -xticksize/4];
patch(x,y,[0 0 0])
axis off;
box off;
if nargout > 0,
    out.xaxis = xax;
    out.yaxis = yax;
    out.xtick = newxtick;
    out.ytick = newytick;
    out.xticklabel = newxticklab;
    out.yticklabel = newyticklab;
    out.newxlabel = newxlabel;
    out.newylabel = newylabel;
end;