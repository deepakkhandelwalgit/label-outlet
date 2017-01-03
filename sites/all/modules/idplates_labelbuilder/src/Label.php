<?php

class Label {
  public $size;
  public $layout;
  public $text;
  public $tag_color;
  public $numbering;
  public $barcode;
  public $cost;
  private $nid;
  private $size_tid;
  private $layout_tid;
  private $section;

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

}
