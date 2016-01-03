<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="2.3.3.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="640.0000" Y="960.0000" />
        <Children>
          <AbstractNodeData Name="bg_story_1" ActionTag="259027702" Tag="3" IconVisible="False" LeftMargin="0.0002" RightMargin="-0.0002" ctype="SpriteObjectData">
            <Size X="640.0000" Y="960.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="320.0002" Y="480.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5000" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="Image/bg_story.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="menu_button" ActionTag="-1373099952" Tag="33" IconVisible="False" LeftMargin="-9.5500" RightMargin="529.5500" TopMargin="870.0000" BottomMargin="-30.0000" Scale9Width="120" Scale9Height="120" ctype="ImageViewObjectData">
            <Size X="120.0000" Y="120.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="50.4500" Y="30.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0788" Y="0.0313" />
            <PreSize X="0.1875" Y="0.1250" />
            <FileData Type="Normal" Path="Image/button_info_normal_home.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Board" ActionTag="1429186130" Tag="10" IconVisible="False" LeftMargin="20.0000" RightMargin="20.0000" TopMargin="180.0000" BottomMargin="200.0000" TouchEnable="True" BackColorAlpha="102" ComboBoxIndex="1" ColorAngle="90.0000" Scale9Width="1" Scale9Height="1" ctype="PanelObjectData">
            <Size X="600.0000" Y="580.0000" />
            <AnchorPoint />
            <Position X="20.0000" Y="200.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0313" Y="0.2083" />
            <PreSize X="0.9375" Y="0.6042" />
            <SingleColor A="255" R="150" G="200" B="255" />
            <FirstColor A="255" R="150" G="200" B="255" />
            <EndColor A="255" R="255" G="255" B="255" />
            <ColorVector ScaleY="1.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="count_turn" ActionTag="-2013181577" Tag="32" IconVisible="False" LeftMargin="477.6364" RightMargin="22.3636" TopMargin="898.4090" BottomMargin="15.5910" LabelText="100/100" ctype="TextBMFontObjectData">
            <Size X="140.0000" Y="46.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="547.6364" Y="38.5910" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8557" Y="0.0402" />
            <PreSize X="0.2188" Y="0.0479" />
            <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="point" ActionTag="593087427" Tag="26" IconVisible="False" LeftMargin="433.0000" RightMargin="10.0000" TopMargin="97.0000" BottomMargin="817.0000" LabelText="1000000000" ctype="TextBMFontObjectData">
            <Size X="197.0000" Y="46.0000" />
            <AnchorPoint ScaleX="1.0000" ScaleY="0.5000" />
            <Position X="630.0000" Y="840.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9844" Y="0.8750" />
            <PreSize X="0.3078" Y="0.0479" />
            <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="counts" ActionTag="-1007830183" Tag="27" IconVisible="True" LeftMargin="180.0000" RightMargin="460.0000" TopMargin="80.0000" BottomMargin="880.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="icon_0" ActionTag="-556516422" Tag="7" IconVisible="False" LeftMargin="-40.0000" RightMargin="-40.0000" TopMargin="-80.0000" ctype="SpriteObjectData">
                <Size X="80.0000" Y="80.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position Y="40.0000" />
                <Scale ScaleX="0.4000" ScaleY="0.4000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="Image/icon_skull.png" Plist="Scene/MainScene/MainScene.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_1" ActionTag="1272457335" Tag="5" IconVisible="False" LeftMargin="60.0000" RightMargin="-140.0000" TopMargin="-80.0000" ctype="SpriteObjectData">
                <Size X="80.0000" Y="80.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="100.0000" Y="40.0000" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="Image/icon_pumpkin.png" Plist="Scene/MainScene/MainScene.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_2" ActionTag="624552279" Tag="10" IconVisible="False" LeftMargin="160.0000" RightMargin="-240.0000" TopMargin="-80.0000" ctype="SpriteObjectData">
                <Size X="80.0000" Y="80.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="200.0000" Y="40.0000" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="Image/icon_soul.png" Plist="Scene/MainScene/MainScene.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_3" ActionTag="1667732652" Tag="12" IconVisible="False" LeftMargin="260.0000" RightMargin="-340.0000" TopMargin="-80.0000" ctype="SpriteObjectData">
                <Size X="80.0000" Y="80.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="300.0000" Y="40.0000" />
                <Scale ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="MarkedSubImage" Path="Image/icon_star_off.png" Plist="Scene/MainScene/MainScene.plist" />
                <BlendFunc Src="770" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="icon_4" ActionTag="1886925383" Tag="13" IconVisible="False" LeftMargin="385.5000" RightMargin="-414.5000" TopMargin="-63.0000" BottomMargin="17.0000" LabelText="C" ctype="TextBMFontObjectData">
                <Size X="29.0000" Y="46.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="400.0000" Y="40.0000" />
                <Scale ScaleX="1.5000" ScaleY="1.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="count_0" ActionTag="-445714848" Tag="8" IconVisible="False" LeftMargin="-51.0000" RightMargin="-51.0000" TopMargin="-23.0000" BottomMargin="-23.0000" LabelText="00/00" ctype="TextBMFontObjectData">
                <Size X="102.0000" Y="46.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="count_1" ActionTag="-851579265" Tag="9" IconVisible="False" LeftMargin="49.0000" RightMargin="-151.0000" TopMargin="-23.0000" BottomMargin="-23.0000" LabelText="00/00" ctype="TextBMFontObjectData">
                <Size X="102.0000" Y="46.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="100.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="count_2" ActionTag="-464439381" Tag="11" IconVisible="False" LeftMargin="149.0000" RightMargin="-251.0000" TopMargin="-23.0000" BottomMargin="-23.0000" LabelText="00/00" ctype="TextBMFontObjectData">
                <Size X="102.0000" Y="46.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="200.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="count_3" ActionTag="1341008881" Tag="13" IconVisible="False" LeftMargin="249.0000" RightMargin="-351.0000" TopMargin="-23.0000" BottomMargin="-23.0000" LabelText="00/00" ctype="TextBMFontObjectData">
                <Size X="102.0000" Y="46.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="300.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="count_4" ActionTag="-661567336" Tag="7" IconVisible="False" LeftMargin="349.0000" RightMargin="-451.0000" TopMargin="-23.0000" BottomMargin="-23.0000" LabelText="00/00" ctype="TextBMFontObjectData">
                <Size X="102.0000" Y="46.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="400.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <LabelBMFontFile_CNB Type="Normal" Path="Fonts/BasicLabel.fnt" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="180.0000" Y="880.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2813" Y="0.9167" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>