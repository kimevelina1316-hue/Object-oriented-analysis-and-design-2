using System;
using System.IO;

namespace LabReportGenerator
{
    public class ReportDirector_WithoutPattern
    {
        public Report BuildReport(ReportData data)
        {
            var report = new Report();

            string html = $@"
<!DOCTYPE html>
<html>
<head>
    <meta charset='utf-8'>
    <title>{data.Title}</title>
    <style>
        body {{ font-family: Arial, sans-serif; margin: 40px; line-height: 1.6; }}
        h1 {{ text-align: center; border-bottom: 2px solid #333; padding-bottom: 10px; }}
        h2 {{ color: #0056b3; margin-top: 20px; }}
        .header-info {{ background: #f8f9fa; padding: 15px; border-radius: 8px; margin-bottom: 20px; }}
        pre {{ background: #2b2b2b; color: #f8f8f2; padding: 15px; border-radius: 5px; overflow-x: auto; }}
        .placeholder {{ padding: 20px; border: 2px dashed #ccc; text-align: center; color: #777; background: #fafafa; }}
        img {{ max-width: 100%; height: auto; border: 1px solid #ddd; }}
    </style>
</head>
<body>";

            html += $"<h1>{data.Title}</h1>";
            html += $"<div class='header-info'>";
            html += $"<p><strong>Студент:</strong> {data.StudentName}</p>";
            html += $"<p><strong>Группа:</strong> {data.Group}</p>";
            html += $"<p><strong>Дисциплина:</strong> {data.Discipline}</p>";
            html += $"</div>";

            html += $"<h2>Цель работы</h2><p>{data.Goal}</p>";
            html += $"<h2>Задание</h2><p>{data.Task}</p>";
            html += $"<h2>Теоретические сведения</h2><p>{data.Theory}</p>";

            if (data.Discipline == "Базы данных")
            {
                html += $"<h2>Описание экспериментальной установки</h2><p>{data.Experiment}</p>";
                html += $"<h2>ER-диаграмма базы данных</h2>";
                if (!string.IsNullOrEmpty(data.ImagePath))
                    html += $"<img src='file:///{data.ImagePath.Replace("\\", "/")}' alt='ER-схема' />";
                else
                    html += "<p><i>[Изображение не прикреплено]</i></p>";
            }
            else if (data.Discipline == "Компьютерные сети")
            {
                html += $"<h2>Описание экспериментальной установки</h2><p>{data.Experiment}</p>";
                html += $"<h2>Схема компьютерной сети</h2>";
                if (!string.IsNullOrEmpty(data.ImagePath))
                    html += $"<img src='file:///{data.ImagePath.Replace("\\", "/")}' alt='Схема сети' />";
                else
                    html += "<p><i>[Изображение не прикреплено]</i></p>";
            }
            else if (data.Discipline == "Программирование")
            {
                html += $"<h2>Код программы</h2><pre>{data.Experiment}</pre>";
            }

            html += $"<h2>Результаты работы</h2><p>{data.Results}</p>";
            html += $"<h2>Анализ результатов</h2><p>{data.Analysis}</p>";
            html += $"<h2>Выводы</h2><p>{data.Conclusion}</p>";

            html += "</body></html>";

            report.SetHtml(html);
            return report;
        }
    }
}