# Interpolação polinômial (Método de Lagrange)
<p>Esse é um projeto baseado no primeiro projeto de ATP2.</p>
<p>Ele foi criado simplesmente porque o método de Lagrange é muito trabalhoso de calcular para polinômios de grau alto</p>
<p>Desenvolvido por Kayke Guilherme Vertu.</p>
<h1>O que é isso?</h1>
<p>Interpolação polinômial é um método de estimar um polinômio de grau n, dado um conjunto de n + 1 pontos ((x<sub>1</sub>, y<sub>1</sub>), (x<sub>2</sub>, y<sub>2</sub>), ..., (x<sub>n + 1</sub>, y<sub>n + 1</sub>)) tal que: </p>
<ul>
    <li>p(x<sub>1</sub>) = y<sub>1</sub></li>
    <li>p(x<sub>2</sub>) = y<sub>2</sub></li>
    <li>p(x<sub>3</sub>) = y<sub>3</sub></li>
    <li>...</li>
    <li>p(x<sub>n + 1</sub>) = y<sub>n + 1</sub></li>
</ul>
<h1>Como compilar</h1>
<code>gcc poly.c lagrange.c -lm -o lagrange</code>
<p>Obs: o executável para Windows tem que ser compilado localmente para evitar problemas com o Windows Defender</p>