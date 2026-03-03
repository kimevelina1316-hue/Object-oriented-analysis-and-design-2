using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabReportGenerator
{
    public class Report
    {
        private string _htmlContent;

        public string Title { get; set; }
        public string StudentName { get; set; }
        public string Discipline { get; set; }
        public string Goal { get; set; }
        public string Task { get; set; }
        public string Theory { get; set; }
        public string Experiment { get; set; }
        public string Results { get; set; }
        public string Analysis { get; set; }
        public string Conclusion { get; set; }

        public string GetHtml()
        {
            return _htmlContent;
        }

        public void SetHtml(string content)
        {
            _htmlContent = content;
        }
    }
}