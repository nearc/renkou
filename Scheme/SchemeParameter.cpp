#include "SchemeParameter.hpp"
#include <QObject>

std::shared_ptr<ParaHolder> SchemeParameterDefault::paraholder =
std::make_shared<ParaHolder>(ParaHolder{"diqu", "shixian", "duiji", "hunpei", "huji", "koujinplusshiji", "qianyi"});

QString SchemeParameter::generate(schememetadataPtr meta) const {
    return do_generate(meta);
}

SchemeParameterDefault::SchemeParameterDefault():SchemeParameter(paraholder)
{

}

void SchemeParameterDefault::init(void) {
    if (! paraholder) paraholder = std::make_shared<ParaHolder>(ParaHolder());
}

QString SchemeParameterDefault::do_generate(schememetadataPtr meta) const {
 /*地区、政策实现程度（分两种：政策生育、可能生育，可能生育即原来的“回归生育”）、堆积释放模式（分四种：分释、突释、缓释、正常）、
  *婚配概率估计方法（只有多龄概率一种，可不标明。原来还有同龄概率）、户籍（农业、非农）、政策口径(多种)+政策调整时机、迁移强度
  */
    using Category = schememetadata::Category;
    const QString huji = value("huji");
    Category category = meta->category();
    QString categoryStr = scheme::toString(category);
    if(category == Category::FenLingHeJi &&
            (huji == QObject::tr("农业") || huji == QObject::tr("非农"))) {
        categoryStr = QObject::tr("分龄") + huji;
    }

    // 上海农业人口概要_回归分释_多龄_农d11p15_非d11p15_z
    return QObject::tr("%1%2%3_%4%5_%6_%7_%8")
            .arg(value("diqu"),
                 value("huji"),
                 categoryStr,
                 QString(value("shixian")).remove(QObject::tr("生育")),
                 value("duiji"),
                 (value("hunpei").isEmpty() ? QObject::tr("多龄") : value("hunpei")),
                 value("koujinplusshiji"),
                 value("qianyi"));
}
