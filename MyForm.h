
namespace Project1 {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for MyForm
/// </summary>
public ref class MyForm : public System::Windows::Forms::Form
{
public:
MyForm(void)
{
InitializeComponent();
//
//TODO: Add the constructor code here
//
}

protected:
/// <summary>
/// Clean up any resources being used.
/// </summary>
~MyForm()
{
if (components)
{
delete components;
}
}

private:
// --- ЗАДАЧА 1: Крива Без'є ---
void DrawBezierCurve(Graphics^ g, Pen^ pen, PointF p1, PointF p2, PointF p3, PointF p4) {
PointF prevPoint = p1;
for (float t = 0; t <= 1.0f; t += 0.005f) {
float u = 1 - t;
float x = u * u * u * p1.X + 3 * u * u * t * p2.X + 3 * u * t * t * p3.X + t * t * t * p4.X;
float y = u * u * u * p1.Y + 3 * u * u * t * p2.Y + 3 * u * t * t * p3.Y + t * t * t * p4.Y;
PointF currPoint = PointF(x, y);
g->DrawLine(pen, prevPoint, currPoint);
prevPoint = currPoint;
}
}
// --- ЗАДАЧА 2: Фрактал Коха ---
void DrawKochLine(Graphics^ g, Pen^ pen, PointF p1, PointF p5, int k) {
if (k == 0) {
g->DrawLine(pen, p1, p5);
}
else {
float dx = p5.X - p1.X;
float dy = p5.Y - p1.Y;
PointF p2(p1.X + dx / 3.0f, p1.Y + dy / 3.0f);
PointF p4(p1.X + 2 * dx / 3.0f, p1.Y + 2 * dy / 3.0f);

float angle = -Math::PI / 3.0f;
float vx = p4.X - p2.X;
float vy = p4.Y - p2.Y;
PointF p3(p2.X + vx * Math::Cos(angle) - vy * Math::Sin(angle),
p2.Y + vx * Math::Sin(angle) + vy * Math::Cos(angle));
DrawKochLine(g, pen, p1, p2, k - 1);
DrawKochLine(g, pen, p2, p3, k - 1);
DrawKochLine(g, pen, p3, p4, k - 1);
DrawKochLine(g, pen, p4, p5, k - 1);
}
}

void DrawKochSnowflake(Graphics^ g, Pen^ pen, PointF p1, PointF p2, PointF p3, int k) {
DrawKochLine(g, pen, p1, p2, k);
DrawKochLine(g, pen, p2, p3, k);
DrawKochLine(g, pen, p3, p1, k);
}

/// <summary>
/// Required designer variable.
/// </summary>
System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
/// <summary>
/// Required method for Designer support - do not modify
/// the contents of this method with the code editor.
/// </summary>
void InitializeComponent(void)
{
this->SuspendLayout();
//
// MyForm
//
this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
this->ClientSize = System::Drawing::Size(402, 357);
this->Name = L"MyForm";
this->Text = L"MyForm";
this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
this->ResumeLayout(false);

}
#pragma endregion
private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {

Graphics^ g = e->Graphics;
g->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::HighQuality;

// 1. Малюємо Без'є (Червона)
Pen^ redPen = gcnew Pen(Color::Red, 2);
DrawBezierCurve(g, redPen, PointF(50, 300), PointF(100, 50), PointF(300, 50), PointF(350, 300));

// 2. Малюємо Сніжинку (Синя)
Pen^ bluePen = gcnew Pen(Color::Blue, 1);
DrawKochSnowflake(g, bluePen, PointF(650, 100), PointF(800, 400), PointF(500, 400), 4);
}
  };
 }
