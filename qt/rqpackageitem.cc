
#include <qstring.h>

#include <rpackage.h>

#include <rqpackageitem.h>
#include <rqpixmaps.h>

#include <iostream>

RQPackageItem::RQPackageItem(QListView *parent, RPackage *pkg)
   : QListViewItem(parent), pkg(pkg)
{
}

QString RQPackageItem::text(int column) const
{
   QString res;

   switch (column) {

      case 1:
         res = pkg->name();
         break;

      case 2:
         res = pkg->installedVersion();
         break;

      case 3:
         res = pkg->availableVersion();
         break;

      default:
         res = QString::null;
         break;
   }

   return res;
}

void RQPackageItem::paintCell(QPainter *p, const QColorGroup &cg,
                             int column, int width, int align)
{
   if (column == 0) {
      int flags = pkg->getFlags();

      if (pkg->wouldBreak()) {
         _pm = RQPixmaps::find("package-broken.png");
      } else if (flags & RPackage::FNewInstall) {
         _pm = RQPixmaps::find("package-install.png");
      } else if (flags & RPackage::FUpgrade) {
         _pm = RQPixmaps::find("package-upgrade.png");
      } else if (flags & RPackage::FReInstall) {
         _pm = RQPixmaps::find("package-reinstall.png");
      } else if (flags & RPackage::FDowngrade) {
         _pm = RQPixmaps::find("package-downgrade.png");
      } else if (flags & RPackage::FPurge) {
         _pm = RQPixmaps::find("package-purge.png");
      } else if (flags & RPackage::FRemove) {
         _pm = RQPixmaps::find("package-remove.png");
      } else if (flags & RPackage::FInstalled) {
         if (flags & RPackage::FPinned)
            _pm = RQPixmaps::find("package-installed-locked.png");
         else if (flags & RPackage::FOutdated)
            _pm = RQPixmaps::find("package-installed-outdated.png");
         else
            _pm = RQPixmaps::find("package-installed-updated.png");
      } else {
         if (flags & RPackage::FPinned)
            _pm = RQPixmaps::find("package-available-locked.png");
         else if (flags & RPackage::FNew)
            _pm = RQPixmaps::find("package-new.png");
         else
            _pm = RQPixmaps::find("package-available.png");
      }
   }

   QListViewItem::paintCell(p, cg, column, width, align);
}

const QPixmap *RQPackageItem::pixmap(int column) const
{
   return (column == 0) ? &_pm : NULL;
}

// vim:ts=3:sw=3:et