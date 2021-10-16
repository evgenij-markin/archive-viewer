#include <QFileDialog>

#include "mainwindow.h"

// minizip libraries
#include "mz.h"
#include "mz_os.h"
#include "mz_strm.h"
#include "mz_strm_buf.h"
#include "mz_strm_split.h"
#include "mz_zip.h"
#include "mz_zip_rw.h"

#include <stdio.h>  /* printf */


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , tableView(new QTableView(this))
{
    setWindowTitle(tr("ZIP-Archive Viewer") );

    // Создаём элементы управления на главном окне (кнопки,  таблицы, метки и т.п.)

    wdg = new QWidget(this);
    wdg->setMinimumSize(650, 500);
    vlay = new QVBoxLayout(wdg);

    btn1 = new QPushButton(tr("Выберите zip-архив...") );
    btn1->setStyleSheet("font-size: 15px;font: bold;");
    vlay->addWidget(btn1);

    label1 = new QLabel(tr(" Название архива:") );
    label1->setStyleSheet("font-size: 15px; background-color: rgb(250, 250, 240); font: bold;");
    label1->setWordWrap(true);
    vlay->addWidget(label1);

//    tableView->setEnabled(false);
//    tableView->setVisible(false);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView->setAlternatingRowColors(true);
    tableView->setStyleSheet("alternate-background-color: rgb(198, 225, 237); font-size: 15px;");
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout = new QHBoxLayout();
    layout->addWidget(tableView);

    vlay->addLayout(layout);

    wdg->setLayout(vlay);

    setCentralWidget(wdg);

    connect(btn1, SIGNAL( clicked() ), this, SLOT( OnBtn1Clicked() ) );
}

MainWindow::~MainWindow()
{
}

void MainWindow::OnBtn1Clicked()
{
    QString fileName{};
    const QString archive_type = "Archive zip-files (*.zip)";

    fileName = QFileDialog::getOpenFileName(this, tr("Открыть файл"),
                                                  QDir::currentPath(),
                                                  archive_type);
    if( fileName.isEmpty() )
        return;

    label1->setStyleSheet("font-size: 15px; background-color: rgb(250, 250, 240); font: bold;");
    label1->setText(tr(" Архив: ") + fileName);

    arch_contents.clear();

    // convert QString -> const char *
    QByteArray tmp_byte_flname = fileName.toLocal8Bit();
    const char *full_flname = tmp_byte_flname.constData();

    // get zip-archive contents
    if (int32_t resultCode = minizip_list(full_flname) )
    {
        label1->setStyleSheet("font-size: 15px; background-color: rgb(250, 0, 0); font: bold;");
        label1->setText(tr("Архив ") + fileName + tr(" повреждён. Код ошибки ") +
                        QString("%1").arg(resultCode) );
    };

    tableView->verticalScrollBar()->setValue(0);

    MyModel *myModel1 = new MyModel(this);
    myModel1->setVector(&arch_contents);
    tableView->setModel(myModel1);
}

/***************************************************************************/

int32_t MainWindow::minizip_list(const char *path) {

    Archive_info my_archive;

    mz_zip_file *file_info = NULL;
    uint32_t ratio = 0;
    int32_t err = MZ_OK;
    struct tm tmu_date;
    const char *method = NULL;
    char crypt = ' ';
    void *reader = NULL;


    mz_zip_reader_create(&reader);
    err = mz_zip_reader_open_file(reader, path);
    if (err != MZ_OK) {
        printf("Error %" PRId32 " opening archive %s\n", err, path);
        mz_zip_reader_delete(&reader);
        return err;
    }

    err = mz_zip_reader_goto_first_entry(reader);

    if (err != MZ_OK && err != MZ_END_OF_LIST) {
        printf("Error %" PRId32 " going to first entry in archive\n", err);
        mz_zip_reader_delete(&reader);
        return err;
    }

    printf("      Packed     Unpacked Ratio Method   Attribs Date     Time  CRC-32     Name\n");
    printf("      ------     -------- ----- ------   ------- ----     ----  ------     ----\n");

    /* Enumerate all entries in the archive */
    do {
        err = mz_zip_reader_entry_get_info(reader, &file_info);

        if (err != MZ_OK) {
            printf("Error %" PRId32 " getting entry info in archive\n", err);
            break;
        }

        ratio = 0;
        if (file_info->uncompressed_size > 0)
            ratio = (uint32_t)((file_info->compressed_size * 100) / file_info->uncompressed_size);

        /* Display a '*' if the file is encrypted */
        if (file_info->flag & MZ_ZIP_FLAG_ENCRYPTED)
            crypt = '*';
        else
            crypt = ' ';

        method = mz_zip_get_compression_method_string(file_info->compression_method);
        mz_zip_time_t_to_tm(file_info->modified_date, &tmu_date);

        /* Print entry information */
        printf("%12" PRId64 " %12" PRId64 "  %3" PRIu32 "%% %6s%c %8" PRIx32 " %2.2" PRIu32 \
               "-%2.2" PRIu32 "-%2.2" PRIu32 " %2.2" PRIu32 ":%2.2" PRIu32 " %8.8" PRIx32 "   %s\n",
               file_info->compressed_size, file_info->uncompressed_size, ratio,
               method, crypt, file_info->external_fa,
               (uint32_t)tmu_date.tm_mon + 1, (uint32_t)tmu_date.tm_mday,
               (uint32_t)tmu_date.tm_year % 100,
               (uint32_t)tmu_date.tm_hour, (uint32_t)tmu_date.tm_min,
               file_info->crc, file_info->filename);

        // Add to vector
        my_archive.filename = static_cast<QString>(file_info->filename);
        my_archive.compressed_size = file_info->compressed_size;
        my_archive.uncompressed_size = file_info->uncompressed_size;
        arch_contents.push_back(my_archive);
        //qDebug() << arch_contents.at(0).filename;

        err = mz_zip_reader_goto_next_entry(reader);

        if (err != MZ_OK && err != MZ_END_OF_LIST) {
            printf("Error %" PRId32 " going to next entry in archive\n", err);
            break;
        }
    } while (err == MZ_OK);

    mz_zip_reader_delete(&reader);

    if (err == MZ_END_OF_LIST)
        return MZ_OK;

    return err;
}
