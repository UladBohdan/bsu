#include "mainwindow.h"
#include "ui_mainwindow.h"

// THE ALGORITHM ///////////////////////////////////////////////////////////////

const double INF = 9999999999;

double inline dist(QPoint& a, QPoint& b) {
  return std::sqrt((a.x() - b.x()) * (a.x() - b.x()) +
                   (a.y() - b.y()) * (a.y() - b.y()));
}

QVector<QPair<int, int>>
CalculateDelaunayTriangularion(QVector<QPoint>& points) {
  const QString FILE_PREFIX = "temp0";
  const QString NODES_FILENAME = FILE_PREFIX + ".node";
  const QString NODES_FILENAME_ALT = FILE_PREFIX + ".1.node";
  const QString ELE_FILENAME = FILE_PREFIX + ".1.ele";

  if (QFileInfo(NODES_FILENAME).exists()) {
    QFile(NODES_FILENAME).remove();
  }
  if (QFileInfo(NODES_FILENAME_ALT).exists()) {
    QFile(NODES_FILENAME_ALT).remove();
  }
  if (QFileInfo(ELE_FILENAME).exists()) {
    QFile(ELE_FILENAME).remove();
  }

  QFile nodesFile(NODES_FILENAME);
  if (!nodesFile.open(QIODevice::ReadWrite)) {
    return QVector<QPair<int, int>>();
  }

  QTextStream stream(&nodesFile);
  stream << points.size() << " 2 0 0\n";
  for (int i = 0; i < points.size(); i++) {
    stream << i+1 << " " << points[i].x() << " " << points[i].y() << "\n";
  }

  nodesFile.close();

  QProcess triangulation_process;
  triangulation_process.start("triangle", QStringList() << FILE_PREFIX);
  triangulation_process.waitForFinished();

  QFile trianglesFile(ELE_FILENAME);
  if (!trianglesFile.open(QIODevice::ReadOnly)) {
    return QVector<QPair<int, int>>();
  }

  QVector<QPair<int, int>> edges;

  QTextStream stream2(&trianglesFile);
  QString temp_line;
  temp_line = stream2.readLine();
  int number_of_triangles = 0, nodes_per_triangle = 0, number_of_attr = 0;
  QTextStream(&temp_line) >> number_of_triangles >> nodes_per_triangle
                          >> number_of_attr;
  for (int i = 0; i < number_of_triangles; i++) {
    temp_line = stream2.readLine();
    int n_triangle = 0, node1 = 0, node2 = 0, node3 = 0;
    QTextStream(&temp_line) >> n_triangle >> node1 >> node2 >> node3;
    edges.push_back(QPair<int, int>(node1 - 1, node2 - 1));
    edges.push_back(QPair<int, int>(node1 - 1, node3 - 1));
    edges.push_back(QPair<int, int>(node2 - 1, node3 - 1));
  }

  trianglesFile.close();

  return edges;
}

QVector<QPair<QPoint, QPoint>>
Prima_Dijkstra_MlogN(QVector<QPoint>& points, QVector<QPair<int, int>> graph) {
  // Edge is distance + indices of two points.
  typedef std::pair<double,std::pair<int,int>> Edge;

  const int sz = points.size();

  auto cmp = [](Edge left, Edge right) { return left.first > right.first;};
  std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> q(cmp);

  QVector<QPair<QPoint, QPoint>> edges;
  edges.reserve(sz - 1);

  // Morph graph from list of edges into a list of incidency.
  QVector<QList<int>> g(sz, QList<int>());
  for (QPair<int, int>& edge : graph) {
    g[edge.first].push_back(edge.second);
    g[edge.second].push_back(edge.first);
  }

  QVector<bool> used(sz, false);

  // 0 is the first point to be added.
  for (int node : g[0]) {
    std::pair<int, int> edge(0, node);
    q.push(Edge(dist(points[0], points[node]), edge));
  }
  used[0] = true;

  while (edges.size() != sz - 1) {
    Edge min_edge;
    int new_node;
    while (true) {
      min_edge = q.top();
      bool a = used[min_edge.second.first];
      bool b = used[min_edge.second.second];
      if (a ^ b) {
        if (!a) {
          new_node = min_edge.second.first;
        } else {
          new_node = min_edge.second.second;
        }
        break;
      } else {
          q.pop();
      }
    }
    q.pop();

    edges.push_back(QPair<QPoint, QPoint>(points[min_edge.second.first],
                    points[min_edge.second.second]));

    used[new_node] = true;

    for (int node : g[new_node]) {
      if (!used[node]) {
        std::pair<int, int> edge(new_node, node);
        q.push(Edge(dist(points[new_node], points[node]), edge));
      }
    }
  }

  return edges;
}

QVector<QPair<QPoint, QPoint>> Prima_Dijkstra_N3(QVector<QPoint>& points) {
  const int sz = points.size();

  QVector<QVector<double>> matr(sz, QVector<double>(sz));
  for (int i = 0; i < matr.size(); i++) {
    for (int j = 0; j < matr[0].size(); j++) {
      matr[i][j] = dist(points[i], points[j]);
    }
  }

  QVector<QPair<QPoint, QPoint>> edges;
  edges.reserve(sz - 1);

  QVector<bool> used(sz, false);

  used.push_back(0);
  used[0] = true;

  while (edges.size() != sz - 1) {
    double new_min_dist = INF;
    int min_start, min_end;
    for (int i = 0; i < sz; i++) {
      if (used[i]) {
        for (int j = 0; j < sz; j++) {
          if (!used[j]) {
            if (dist(points[i], points[j]) < new_min_dist) {
              min_start = i;
              min_end = j;
              new_min_dist = dist(points[i], points[j]);
            }
          }
        }
      }
    }
    edges.push_back(QPair<QPoint, QPoint>(points[min_start], points[min_end]));
    used[min_end] = true;
  }

  return edges;
}

QVector<QPair<QPoint, QPoint>>
Prima_Dijkstra_FullGraph(QVector<QPoint>& points) {
  QVector<QPair<int, int>> full_graph;
  for (int i = 0; i < points.size(); i++) {
    for (int j = i + 1; j < points.size(); j++) {
      full_graph.push_back(QPair<int, int>(i, j));
    }
  }
  return Prima_Dijkstra_MlogN(points, full_graph);
}

QVector<QPair<QPoint, QPoint>>
Prima_Dijkstra_Triangulation(QVector<QPoint>& points,
                             QVector<QPair<int, int>> triangulation) {
  return Prima_Dijkstra_MlogN(points, triangulation);
}

// THE END OF THE ALGORITHM ////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  points_.push_back(event->pos());
  repaint();
}

void MainWindow::paintEvent(QPaintEvent*) {
  QPainter p(this);
  p.setPen(Qt::black);
  p.setBrush(QBrush(Qt::black));
  for (QPoint point : points_) {
    p.drawEllipse(point, 3, 3);
  }

  p.setPen(Qt::gray);
  for (QPair<int, int> edge : triangulation_) {
    p.drawLine(points_[edge.first], points_[edge.second]);
  }

  p.setPen(Qt::black);
  for (QPair<QPoint, QPoint> edge : edges_) {
    p.drawLine(edge.first, edge.second);
  }
}

void MainWindow::on_pushButton_2_clicked() {
  triangulation_.clear();
  edges_ = Prima_Dijkstra_N3(points_);
  repaint();
}

void MainWindow::on_pushButton_3_clicked() {
  triangulation_.clear();
  edges_ = Prima_Dijkstra_FullGraph(points_);
  repaint();
}

void MainWindow::on_pushButton_4_clicked() {
  triangulation_ = CalculateDelaunayTriangularion(points_);
  edges_ = Prima_Dijkstra_Triangulation(points_, triangulation_);
  repaint();
}
