using System;
using System.IO;
using System.Text;

namespace LabReportGenerator
{
    public class HtmlReportBuilder : IReportBuilder
    {
        private StringBuilder _html = new StringBuilder();
        private string _currentDiscipline = "";
        private string _imagePath = "";
        private string _code = "";

        public void AddHeader(string title, string student, string group)
        {
            _html.Append(@"<html><head><meta charset='utf-8'><title>" + title + @"</title>
            <style>body{font-family:Arial; max-width:1000px; margin:30px auto;} img{max-width:100%; border:1px solid #ccc;} pre{background:#f4f4f4; padding:15px; overflow-x:auto;}</style>
            </head><body>");
            _html.AppendLine($"<h1>{title}</h1>");
            _html.AppendLine($"<p><b>Студент:</b> {student} | <b>Группа:</b> {group}</p><hr>");
        }

        public void AddSections(string goal, string task, string theory)
        {
            _html.AppendLine($"<h2>Цель</h2><p>{goal}</p>");
            _html.AppendLine($"<h2>Задание</h2><p>{task}</p>");
            _html.AppendLine($"<h2>Теория</h2><p>{theory}</p>");
        }

        public void AddDisciplineSpecific(string discipline, string experiment, string imagePath, string code)
        {
            _currentDiscipline = discipline;
            _imagePath = imagePath;
            _code = code;

            if (discipline == "Базы данных" || discipline == "Компьютерные сети")
            {
                _html.AppendLine($"<h2>Эксперимент</h2><p>{experiment}</p>");
                if (!string.IsNullOrEmpty(imagePath))
                {
                    string fileName = Path.GetFileName(imagePath);
                    File.Copy(imagePath, Path.Combine(AppDomain.CurrentDomain.BaseDirectory, fileName), true);
                    string label = discipline == "Базы данных" ? "ER-диаграмма" : "Схема сети";
                    _html.AppendLine($"<h2>{label}</h2><img src='{fileName}' alt='Image'>");
                }
            }
            else if (discipline == "Программирование")
            {
                string content = !string.IsNullOrEmpty(code) ? code : experiment;
                _html.AppendLine($"<h2>Код программы</h2><pre>{content.Replace("<", "&lt;").Replace(">", "&gt;")}</pre>");
            }
        }

        public void AddFooter(string results, string analysis, string conclusion)
        {
            _html.AppendLine($"<h2>Результаты</h2><p>{results}</p>");
            _html.AppendLine($"<h2>Анализ</h2><p>{analysis}</p>");
            _html.AppendLine($"<h2>Выводы</h2><p>{conclusion}</p>");
            _html.AppendLine("</body></html>");
        }

        public Report GetResult()
        {
            Report r = new Report();
            r.SetHtml(_html.ToString());
            return r;
        }
    }
}