<?php

class Label {
  public $size;
  public $numbering;
  public $review;
  public $notes;
  private $tag_color;
  private $text;
  private $layout;
  private $nid;
  private $size_tid;
  private $layout_tid;
  private $section;
  private $adhesive;
  private $logo;
  private $extras;

  /**
   * @return mixed
   */
  public function getNid() {
    return $this->nid;
  }

  /**
   * @param mixed $nid
   */
  public function setNid($nid) {
    $this->nid = $nid;
  }

  /**
   * @return mixed
   */
  public function getSizeTid() {
    return $this->size_tid;
  }

  /**
   * @param mixed $size_tid
   */
  public function setSizeTid($size_tid) {
    $this->size_tid = $size_tid;
  }

  /**
   * @return mixed
   */
  public function getLayoutTid() {
    return $this->layout_tid;
  }

  /**
   * @param mixed $layout_tid
   */
  public function setLayoutTid($layout_tid) {
    $this->layout_tid = $layout_tid;
  }

  /**
   * @return mixed
   */
  public function getSection() {
    return $this->section;
  }

  /**
   * @param mixed $section
   */
  public function setSection($section) {
    $this->section = $section;
  }

  /**
   * @return mixed
   */
  public function getLayout() {
    return $this->layout;
  }

  /**
   * @param mixed $layout
   */
  public function setLayout($layout) {
    $this->layout = $layout;
  }

  /**
   * @return mixed
   */
  public function getText() {
    return $this->text;
  }

  /**
   * @param mixed $text
   */
  public function setText($text) {
    $this->text = $text;
  }

  /**
   * @return mixed
   */
  public function getTagColor() {
    return $this->tag_color;
  }

  /**
   * @param mixed $tag_color
   */
  public function setTagColor($tag_color) {
    $this->tag_color = $tag_color;
  }

  /**
   * @return mixed
   */
  public function getAdhesive() {
    return $this->adhesive;
  }

  /**
   * @param mixed $adhesive
   */
  public function setAdhesive($adhesive) {
    $this->adhesive = $adhesive;
  }

  /**
   * @return mixed
   */
  public function getLogo() {
    return $this->logo;
  }

  /**
   * @param mixed $logo
   */
  public function setLogo($logo) {
    $this->logo = $logo;
  }

  /**
   * @return mixed
   */
  public function getExtras() {
    return $this->extras;
  }

  /**
   * @param mixed $extras
   */
  public function setExtras($extras) {
    $this->extras = $extras;
  }

}
