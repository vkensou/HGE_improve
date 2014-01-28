Attribute VB_Name = "ModBinPacking"
Option Explicit

Private Type Gene
  BlockID As Long
  Left As Long
  Top As Long
  Right As Long
  Bottom As Long
End Type

Private Type Individual
  geneSequences() As Gene
  Width As Long
  Height As Long
  fitness As Single
  selectprop As Single
  cumulateprop As Single
End Type

Public Type Block
  Left As Long
  Top As Long
  Width As Long
  Height As Long
End Type

Private Type FreeSpace
  Height As Long
  Width As Long
  begin As Long
End Type


Private Function SwapGene(ByRef indi As Individual, indexa As Long, indexb As Long) As Long
  Dim t As Gene
  t = indi.geneSequences(indexa)
  indi.geneSequences(indexa) = indi.geneSequences(indexb)
  indi.geneSequences(indexb) = t
End Function

Private Function CopyGene(ByRef DestIndi As Individual, ByRef SrcIndi As Individual) As Long
  DestIndi = SrcIndi
  Exit Function
  Dim i As Long
  DestIndi.Width = SrcIndi.Width
  DestIndi.Height = SrcIndi.Height
  ReDim DestIndi.geneSequences(UBound(SrcIndi.geneSequences))
  For i = 1 To UBound(SrcIndi.geneSequences)
    DestIndi.geneSequences(i).BlockID = SrcIndi.geneSequences(i).BlockID
    DestIndi.geneSequences(i).Left = SrcIndi.geneSequences(i).Left
    DestIndi.geneSequences(i).Top = SrcIndi.geneSequences(i).Top
  Next i
End Function

Private Function GenerateChildPopulation(ByRef parent() As Individual, ByRef Blocks() As Block) As Long
  Select_and_copy parent
  Cross parent
  Mutation parent, Blocks
End Function

Private Function Select_and_copy(ByRef population() As Individual) As Long
  Dim p As Single, mem As Long, j As Long, sum As Single
  Dim newpopulation() As Individual
  ReDim newpopulation(UBound(population))
  Dim i As Long
  For i = 1 To UBound(population)
    sum = sum + population(i).fitness
  Next i
  population(1).selectprop = population(1).fitness / sum
  population(1).cumulateprop = population(1).selectprop
  For mem = 2 To UBound(population)
    population(mem).selectprop = population(mem).fitness / sum
    population(mem).cumulateprop = population(mem - 1).cumulateprop + population(mem).selectprop
  Next mem
  For i = 1 To UBound(population)
    p = Rnd
    If p < population(1).cumulateprop Then
      CopyGene newpopulation(i), population(1)
    Else
      For j = 2 To UBound(population)
        If p >= population(j - 1).cumulateprop And p < population(j).cumulateprop Then
          CopyGene newpopulation(i), population(j)
        End If
      Next j
    End If
  Next i
  
  For i = 1 To UBound(population)
    CopyGene population(i), newpopulation(i)
  Next i
End Function

Private Function Cross(ByRef population() As Individual) As Long
  Dim parentone As Long, parentnum As Long
  Dim x As Single, j As Long
  parentone = 1
  parentnum = 0
  For j = 1 To UBound(population)
    x = Rnd
    If x < 0.8 Then
      parentnum = parentnum + 1
      If parentnum Mod 2 = 0 Then
        Generate_children population(parentone), population(j)
      Else
        parentone = j
      End If
    End If
  Next j
End Function


Private Function Generate_children(ByRef parent1 As Individual, ByRef parent2 As Individual) As Long
  Dim parent1_position As Long, parent1_end As Long, parent2_position As Long, parent2_end As Long
  Dim flag1 As Long, flag2 As Long
  Dim child(1) As Individual
  Dim i As Long, j As Long
  flag1 = 0: flag2 = 1
  parent1_position = 1: parent1_end = 0
  parent2_position = 1: parent2_end = 0
  ReDim child(0).geneSequences(UBound(parent1.geneSequences))
  ReDim child(1).geneSequences(UBound(parent1.geneSequences))
  child(0).Width = parent2.Width
  child(1).Width = parent1.Width
  child(0).geneSequences(1).BlockID = parent1.geneSequences(1).BlockID
  child(1).geneSequences(1).BlockID = parent2.geneSequences(1).BlockID
  For i = 2 To UBound(parent1.geneSequences)
    If flag1 Mod 2 = 1 And parent1_end = 0 Then
      For j = 1 To i
        If parent1_position <= UBound(parent1.geneSequences) Then
          If parent1.geneSequences(parent1_position).BlockID = child(0).geneSequences(j).BlockID Then
            j = 0
            parent1_position = parent1_position + 1
          End If
        Else
          Exit For
        End If
      Next j
      
      If parent1_position <= UBound(parent1.geneSequences) Then
        child(0).geneSequences(i) = parent1.geneSequences(parent1_position)
      Else
        parent1_end = 1
      End If
    End If

    If flag2 Mod 2 = 1 And parent2_end = 0 Then
      For j = 1 To i
        If parent2_position <= UBound(parent2.geneSequences) Then
          If parent2.geneSequences(parent2_position).BlockID = child(0).geneSequences(j).BlockID Then
            j = 0
            parent2_position = parent2_position + 1
          End If
        Else
          Exit For
        End If
      Next j
      
      If parent2_position <= UBound(parent2.geneSequences) Then
        child(0).geneSequences(i) = parent2.geneSequences(parent2_position)
      Else
        parent2_end = 1
      End If
    End If
    flag1 = flag1 + 1
    flag2 = flag2 + 1
  Next i
  flag1 = 1
  flag2 = 0
  parent1_position = 1
  parent2_position = 1
  parent1_end = 0
  parent2_end = 0
  For i = 2 To UBound(parent1.geneSequences)
    If flag1 Mod 2 = 1 And parent1_end = 0 Then
      For j = 1 To i
        If parent1_position <= UBound(parent1.geneSequences) Then
          If parent1.geneSequences(parent1_position).BlockID = child(1).geneSequences(j).BlockID Then
            j = 0
            parent1_position = parent1_position + 1
          End If
        Else
          Exit For
        End If
      Next j
      
      If parent1_position <= UBound(parent1.geneSequences) Then
        child(1).geneSequences(i) = parent1.geneSequences(parent1_position)
      Else
        parent1_end = 1
      End If
    End If

    If flag2 Mod 2 = 1 And parent2_end = 0 Then
      For j = 1 To i
        If parent2_position <= UBound(parent2.geneSequences) Then
          If parent2.geneSequences(parent2_position).BlockID = child(1).geneSequences(j).BlockID Then
            j = 0
            parent2_position = parent2_position + 1
          End If
        Else
          Exit For
        End If
      Next j
      
      If parent2_position <= UBound(parent2.geneSequences) Then
        child(1).geneSequences(i) = parent2.geneSequences(parent2_position)
      Else
        parent2_end = 1
      End If
    End If
    flag1 = flag1 + 1
    flag2 = flag2 + 1
  Next i
  CopyGene parent1, child(0)
  CopyGene parent2, child(1)
End Function

Private Function Mutation(ByRef population() As Individual, ByRef Blocks() As Block) As Long
  Dim m_1 As Long, m_2 As Long
  Dim mem As Long
  For mem = 1 To UBound(population)
    If Rnd < 0.2 Then
      m_1 = Int((UBound(population(mem).geneSequences) - 1 + 1) * Rnd + 1)
      m_2 = Int((UBound(population(mem).geneSequences) - 1 + 1) * Rnd + 1)
      SwapGene population(mem), m_1, m_2
    End If
    GetFitness population(mem), Blocks
    TS population(mem)
  Next mem
End Function


Public Function GetBPSolution(ByRef Blocks() As Block, ByRef w As Long, ByRef h As Long) As Long
  Dim ITime As Long
  Dim CProb As Single, MProb As Single
  Dim BNum As Long
  Dim CurrentPopulation() As Individual
  Dim BestIndividuals() As Individual
  Dim CTime As Long
  Dim totalBArea As Long
  Dim useRatio As Single
  Dim Width1 As Long, Width2 As Long
  Dim n1 As Long, n2 As Long
  Dim BestIndex As Long
  'Initialize Blocks, totalBArea, ITime, CurrentPopulation, BestIndividuals, useRatio, Width1, Width2
  Initialize Blocks, totalBArea, ITime, CurrentPopulation, BestIndividuals, useRatio, n1, n2
  GenerateInitialPopulation Blocks, CurrentPopulation
  BestIndex = 1
  Debug.Print "箱子面积和：" & totalBArea
  For CTime = 1 To ITime
    GenerateChildPopulation CurrentPopulation, Blocks
    If CTime <> 1 Then ReplaceWorst CurrentPopulation, BestIndividuals(CTime - 1)
    CopyGene BestIndividuals(CTime), CurrentPopulation(GetBestIndividual(CurrentPopulation))
    If BestIndividuals(CTime).fitness >= BestIndividuals(BestIndex).fitness Then BestIndex = CTime
    Debug.Print totalBArea / (BestIndividuals(CTime).Width * BestIndividuals(CTime).Height)
  Next CTime
  Dim i As Long
  For i = 1 To UBound(BestIndividuals(BestIndex).geneSequences)
    Blocks(BestIndividuals(BestIndex).geneSequences(i).BlockID).Left = BestIndividuals(BestIndex).geneSequences(i).Left
    Blocks(BestIndividuals(BestIndex).geneSequences(i).BlockID).Top = BestIndividuals(BestIndex).geneSequences(i).Top
  Next i
  w = BestIndividuals(BestIndex).Width
  h = BestIndividuals(BestIndex).Height
  GetBPSolution = BestIndex
End Function

Private Function GetN2(ByVal s As Long) As Long
  Dim d As Double, d1 As Long
  If s <= 0 Then Exit Function
  d = Log(s) / Log(2)
  d1 = Int(d)
  If d > d1 Then d1 = d1 + 1
  GetN2 = d1
End Function

Private Function Initialize(ByRef Blocks() As Block, ByRef totalBArea As Long, ByRef ITime As Long, ByRef CurrentPopulation() As Individual, ByRef BestIndividuals() As Individual, ByRef useRatio As Single, ByRef n1 As Long, ByRef n2 As Long)
  Dim i As Long, tw As Long, w2 As Long
  totalBArea = 0
  For i = 1 To UBound(Blocks)
    totalBArea = totalBArea + Blocks(i).Width * Blocks(i).Height
    tw = tw + Blocks(i).Width
    If w2 < Blocks(i).Width Then w2 = Blocks(i).Width
  Next i
  
  n1 = GetN2(w2 + 1)
  n2 = GetN2(tw + 1)
  'Width1 = w2
  'Width2 = tw
  ReDim CurrentPopulation(1.5 * UBound(Blocks))
  For i = 1 To UBound(CurrentPopulation)
    CurrentPopulation(i).Width = 2 ^ Int((n2 - n1 + 1) * Rnd + n1)
  Next i
  ITime = 50
  ReDim BestIndividuals(ITime)
  useRatio = 1
End Function
Private Function GenerateInitialPopulation(ByRef Blocks() As Block, ByRef CurrentPopulation() As Individual) As Long
  Dim i As Long, m1 As Long, m2 As Long
  ReDim CurrentPopulation(1).geneSequences(UBound(Blocks))
  For i = 1 To UBound(Blocks)
    CurrentPopulation(1).geneSequences(i).BlockID = i
  Next i
  GetFitness CurrentPopulation(1), Blocks
  For i = 2 To UBound(CurrentPopulation)
    CurrentPopulation(i).geneSequences = CurrentPopulation(i - 1).geneSequences
    m1 = Int((UBound(Blocks) - 1 + 1) * Rnd + 1)
    m2 = Int((UBound(Blocks) - 1 + 1) * Rnd + 1)
    SwapGene CurrentPopulation(i), m1, m2
    GetFitness CurrentPopulation(i), Blocks
  Next i
End Function
Private Function ReplaceWorst(ByRef population() As Individual, ByRef best As Individual) As Long
  Dim i As Long, j As Long
  j = 1
  For i = 1 To UBound(population)
    If population(i).fitness < population(j).fitness Then j = i
  Next i
  CopyGene population(j), best
End Function

Private Function GetBestIndividual(ByRef population() As Individual) As Long
  Dim i As Long, j As Long
  GetBestIndividual = 1
  For i = 1 To UBound(population)
    If population(i).fitness > population(GetBestIndividual).fitness Then GetBestIndividual = i
  Next i
End Function



Private Function GetFitness(ByRef indi As Individual, ByRef Blocks() As Block) As Long
  Dim BlockNum As Long, i As Long, j As Long
  Dim NowBlock As Block, fs As FreeSpace
  Dim lowest As Long, begin As Long, spacewidth As Long, enda As Long
  BlockNum = UBound(Blocks) + 1
  Dim containerHeight() As Long
  ReDim containerHeight(indi.Width - 1)
  i = 1
  Do While i < BlockNum
    NowBlock = Blocks(indi.geneSequences(i).BlockID)
    GetLowestPosition NowBlock, indi.Width, containerHeight, fs
    lowest = fs.Height
    begin = fs.begin
    spacewidth = fs.Width
    enda = 0
    enda = begin + NowBlock.Width - 1
    indi.geneSequences(i).Left = begin
    indi.geneSequences(i).Top = lowest
    j = begin
    Do While j <= enda
       'containerHeight(j) = containerHeight(j) + indi.geneSequences(i).Top + NowBlock.Height
       containerHeight(j) = indi.geneSequences(i).Top + NowBlock.Height
       j = j + 1
    Loop
    i = i + 1
  Loop
  
  Dim mh As Long
  mh = containerHeight(0)
  For i = 0 To UBound(containerHeight)
    If mh < containerHeight(i) Then mh = containerHeight(i)
  Next i
  indi.Height = 2 ^ GetN2(mh)
  indi.fitness = 1 / (indi.Height * indi.Width)
End Function

Private Function GetLowestPosition(theBlock As Block, ByVal Width As Long, containerHeight() As Long, ByRef refs As FreeSpace) As Boolean
  Dim i As Long
  Dim fs() As FreeSpace
  ReDim fs(0)
  Dim tempHeight As Long, tempBegin As Long, tempWidth As Long
  Do While i < Width
    tempHeight = containerHeight(i)
    tempBegin = i
    tempWidth = 1
    i = i + 1
    Do While i < Width
      If tempHeight = containerHeight(i) Then
        i = i + 1
        tempWidth = tempWidth + 1
      Else
        Exit Do
      End If
    Loop
    FsListAdd fs, tempHeight, tempBegin, tempWidth
  Loop
  FsListSort fs
  
  For i = 1 To UBound(fs)
    Dim pp As Long
    pp = fs(i).begin - 1
    Do While pp >= 0
      If containerHeight(pp) <= fs(i).Height Then
        fs(i).begin = fs(i).begin - 1
        fs(i).Width = fs(i).Width + 1
        pp = pp - 1
      Else
        Exit Do
      End If
    Loop
    
    If fs(i).Width >= theBlock.Width Then
      refs = fs(i)
      GetLowestPosition = True
      Exit Function
    End If
      
    Dim pn As Long
    pn = fs(i).begin + fs(i).Width
    Do While pn < Width
      If containerHeight(pn) <= fs(i).Height Then
        fs(i).Width = fs(i).Width + 1
        pn = pn + 1
      Else
        Exit Do
      End If
    Loop
      
    If fs(i).Width >= theBlock.Width Then
      refs = fs(i)
      GetLowestPosition = True
      Exit Function
    End If
  Next i
  GetLowestPosition = False
End Function

Private Sub FsListAdd(fs() As FreeSpace, h As Long, b As Long, w As Long)
  ReDim Preserve fs(UBound(fs) + 1)
  With fs(UBound(fs))
    .Width = w
    .Height = h
    .begin = b
  End With
End Sub
Private Sub FsListSort(fs() As FreeSpace)
  Dim i As Long, j As Long
  Dim t As FreeSpace
  For i = 1 To UBound(fs)
    For j = i + 1 To UBound(fs)
      If fs(i).Height > fs(j).Height Then
        t = fs(i)
        fs(i) = fs(j)
        fs(j) = t
      End If
    Next j
  Next i
End Sub

Private Sub TS(ByRef indi As Individual)

End Sub
