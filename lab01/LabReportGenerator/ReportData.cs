using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LabReportGenerator
{
    public class ReportData
    {
        public string Title { get; set; }
        public string StudentName { get; set; }
        public string Group { get; set; }
        public string Discipline { get; set; }
        public string Goal { get; set; }
        public string Task { get; set; }
        public string Theory { get; set; }
        public string Experiment { get; set; }
        public string Results { get; set; }
        public string Analysis { get; set; }
        public string Conclusion { get; set; }

        // Специфичные поля
        public string ImagePath { get; set; }
        public string Code { get; set; }
    }
}